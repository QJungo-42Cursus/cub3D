/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/05 12:17:00 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

t_vec2	get_impact_point(t_vec2 start, float direction, t_map map)
{
	t_vec2		directeur;

	directeur = angle_to_vec2(deg_to_rad(direction));
	while (is_in_map(start, map)
		&& !(map.tiles[(int)start.y][(int)start.x] != FLOOR))
	{
		start.x += directeur.x / 1000.;
		start.y += directeur.y / 1000.;
	}
	return (start);
}

# define PIXEL_RATIO 1

double	abs_diff_with_int(double a)
{
	return (fabs(roundf(a) - a));
}

t_bool	is_x_collision(t_vec2 impact)
{
	return ((t_bool)(abs_diff_with_int(impact.x) < abs_diff_with_int(impact.y)));
}

t_direction get_text_dir(t_vec2 impact, t_vec2 player_pos)
{
	if (is_x_collision(impact))
	{
		if (impact.x > player_pos.x)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (impact.y > player_pos.y)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	draw_column(t_program *prog, int x, double text_pourcentage, t_direction text_dir, double height)
{
	int			img_y;
	t_texture	texture;

	texture = prog->map.textures[text_dir];
	img_y = prog->img_data.size.y / 2. - height / 2.;
	while (img_y < prog->img_data.size.y / 2. + height / 2)
	{
		if (!(img_y < 0 || img_y >= prog->img_data.size.y))
			pixel_to_image(&prog->img_data, new_vec2(x, img_y), texture.pixels[
				(int)(text_pourcentage * texture.size.x) +
				(int)(img_y / prog->img_data.size.y * texture.size.y)]);
		img_y++;
	}
}

/*
void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	float		height = 400;
	t_direction	text_dir;
	double		pourcent;

	x = 0;
	while (x < img_data->size.x)
	{
		direction = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - FOV
			/ 2 + (float)x / (float)img_data->size.x * FOV;
		impact = get_impact_point(prog->player.pos, direction, prog->map);

		text_dir = get_text_dir(impact, prog->player.pos);
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);

		dist = vec2_dist(prog->player.pos, impact);

		draw_column(prog, x, pourcent, text_dir, height / dist);
		x += 1;
	}
}
*/

typedef struct s_ray2 {
	t_vec2i	tile_pos;
	t_vec2	start_p;
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	dist_impact;
	t_vec2	step;
	t_vec2	len;
}	t_ray2;

t_vec2	get_impact2(t_ray2 *ray, t_map *map);
void	set_ray2(t_player p, t_ray2 *ray, float angle);

static int	is_a_wall(t_vec2i coor, t_map map)
{
	if (coor.x >= map.size.x || coor.y >= map.size.y)
	{
		printf("Impact out of scoop");
		return (-1);
	}
	if (coor.x < 0 || coor.y < 0)
	{
		printf("Impact out of scoop");
		return (-1);
	}
	//printf("coor: %d %d", coor.x, coor.y);
	//printf(" %c\n", map.tiles[coor.y][coor.x]);
	return (map.tiles[coor.y][coor.x] == WALL);
}

void	ray_casting_loop(t_program *prog)
{
	int		x;
	t_ray2	ray;
	int		dist;
	t_direction text_dir;
	t_vec2	impact;
	double	pourcent;

	float height = 400;
	float direction;


	x = 0;
	while (x < prog->img_data.size.x / 2)
	{
		direction = vec2_to_angle(prog->player.dir_cam) - deg_to_rad(FOV)
			/ 2 + (float)x / (float)prog->img_data.size.x * deg_to_rad(FOV);
		//printf("direction: %.2f\t", rad_to_deg(direction));
		set_ray2(prog->player, &ray, direction);
		impact = get_impact2(&ray, &prog->map);
		t_vec2 impact2 = get_impact_point(prog->player.pos, rad_to_deg(direction), prog->map);
		if (!(impact.x == impact2.x && impact.y == impact2.y))
		{
			printf("impact : %.2f %.2f\n", impact.x, impact.y);
			printf("impact2: %.2f %.2f\n\n", impact2.x, impact2.y);
		}
		//dist = sqrt((ray.len.x * ray.len.x) + (ray.len.y + ray.len.y));
		dist = vec2_dist(prog->player.pos, impact);


		text_dir = get_text_dir(impact, prog->player.pos);
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);


		draw_column(prog, x, pourcent, text_dir, height /  dist);
		x += 1;
	}
}

void	set_ray2(t_player p, t_ray2 *ray, float angle)
{
	ray->start_p = p.pos;
	ray->tile_pos = new_vec2i((int) p.pos.x, (int) p.pos.y);
	ray->dir.x = p.dir_cam.x * cos(angle) - p.dir_cam.y * sin(angle);
	ray->dir.y = p.dir_cam.x * sin(angle) - p.dir_cam.y * cos(angle);
	//if (((ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y)) != 1)
		//printf("Not normelize vector");
	if (ray->dir.x == 0)
	{
		ray->delta_dist.x = 0;
	}
	else
	{
		ray->delta_dist.x
			= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	}
	if (ray->dir.y == 0)
	{
		ray->delta_dist.y = 0;
	}
	else
	{
		ray->delta_dist.y
			= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	}
	ray->step = new_vec2(1, 1);
	ray->len.x = (ray->tile_pos.x + 1 - p.pos.x) * ray->delta_dist.x;
	ray->len.y = (ray->tile_pos.y + 1 - p.pos.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->len.x = (p.pos.x - ray->tile_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->len.y = (p.pos.y - ray->tile_pos.y) * ray->delta_dist.y;
	}
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->len.x = (p.pos.x - ray->tile_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->len.y = (p.pos.y - ray->tile_pos.y) * ray->delta_dist.y;
	}
}

t_vec2	get_impact2(t_ray2 *ray, t_map *map)
{
	int	hit;
	//int	side;
	int	status;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->len.x += ray->delta_dist.x;
			ray->start_p.x += ray->delta_dist.x;
			ray->tile_pos.x += ray->step.x;
			//side = FALSE;
		}
		else
		{
			ray->len.y += ray->delta_dist.y;
			ray->start_p.y += ray->delta_dist.y;
			ray->tile_pos.y += ray->step.y;
			//side = TRUE;
		}
		/*
		if (ray->tile_pos.x < 0 || ray->tile_pos.y < 0)
			return (new_vec2(-1, -1));
		if (ray->tile_pos.x >= map->size.x || ray->tile_pos.y >= map->size.y)
			return (new_vec2(-1, -1));
			*/
		if (map->tiles[(int)ray->start_p.y][(int)ray->start_p.x] != FLOOR)
			break ;

		status = is_a_wall(new_vec2i((int)ray->start_p.x, (int)ray->start_p.y), *map);
		printf("start_p: %.2f %.2f\n", ray->start_p.x, ray->start_p.y);
		//status = is_a_wall(ray->tile_pos, *map);
		if (status == 1)
			break ;
		else if (status == -1)
		{
			printf("oupss\n");
			exit(0);
		}
	}
	return (new_vec2(ray->len.x + ray->start_p.x, ray->len.y + ray->start_p.y));
}
