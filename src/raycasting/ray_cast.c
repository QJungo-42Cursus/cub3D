/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/06 10:49:16 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	return (tiles[coor.y][coor.x] == WALL);
}

static void	init_ray(t_player player, t_ray *ray)
{
	ray->pos_tile.x = (int)player.pos.x;
	ray->pos_tile.y = (int)player.pos.y;
	ray->side = 0;
	ray->dist_perp = 0;
}

void	set_ray(t_player play, t_ray *ray, float cam)
{
	init_ray(play, ray);

	ray->dir.x = play.dir_cam.x + play.cam_plan.x * cam;
	ray->dir.y = play.dir_cam.y + play.cam_plan.y * cam;

	ray->delta_dist.x = INFINITY;
	ray->delta_dist.y = INFINITY;

	if (ray->dir.x != 0)
		ray->delta_dist.x
			= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	if (ray->dir.y != 0)
		ray->delta_dist.y
			= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));


	ray->step = new_vec2(1, 1);
	ray->pos_ray.x = (ray->pos_tile.x + 1.0 - play.pos.x) * ray->delta_dist.x;
	ray->pos_ray.y = (ray->pos_tile.y + 1.0 - play.pos.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->pos_ray.x = (play.pos.x - ray->pos_tile.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->pos_ray.y = (play.pos.y - ray->pos_tile.y) * ray->delta_dist.y;
	}
	/*
	if (ray->pos_ray.x == INFINITY)
		ray->pos_ray.x = play.pos.x;
	if (ray->pos_ray.y == INFINITY)
		ray->pos_ray.y = play.pos.y;
		*/
}

t_vec2	get_impact(t_ray *ray, t_map *map)
{
	t_vec2	impact;// = new_vec2(ray->.x

	t_vec2i moves = new_vec2i(0, 0);
	impact = new_vec2(0, 0);
	while (TRUE)
	{
		if (ray->pos_ray.x < ray->pos_ray.y)
		{
			moves.x++;
			//impact.x += ray->delta_dist.x;
			ray->pos_ray.x += ray->delta_dist.x;
			ray->pos_tile.x += ray->step.x;
			ray->side = 1;
		}
		else
		{
			moves.y++;
			//impact.y += ray->delta_dist.y;
			ray->pos_ray.y += ray->delta_dist.y;
			ray->pos_tile.y += ray->step.y;
			ray->side = 0;
		}
		if (is_a_wall(ray->pos_tile, map->tiles))
		{
			//printf("ray->pos_tile.x = %d, ray->pos_tile.y = %d \n", ray->pos_tile.x, ray->pos_tile.y);
			//printf("ray->pos_ray.x = %f, ray->pos_ray.y = %f \n", ray->pos_ray.x, ray->pos_ray.y);
			//printf("impact.x = %f, impact.y = %f \n", impact.x, impact.y);
			//printf("moves.x = %d, moves.y = %d \n", moves.x, moves.y);
			//printf("========\n");
			//double hypothenuse = sqrt(moves.x * moves.x + moves.y * moves.y);
			//y-position is known to be mapY + (1 - stepY) / 2
			break ;
		}
	}
	if (ray->side == 1)
		ray->dist_perp = (ray->pos_ray.x - ray->delta_dist.x);
	else
		ray->dist_perp = (ray->pos_ray.y - ray->delta_dist.y);
	return (impact);
}

void	get_texture_from_ray(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	else
	{
		if (ray->dir.x > 0)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
}

double	abs_diff_with_int(double a)
{
	return (fabs(roundf(a) - a));
}

t_bool	is_x_collision(t_vec2 impact)
{
	return ((t_bool)(abs_diff_with_int(impact.x) < abs_diff_with_int(impact.y)));
}

void	ray_casting_loop(t_program *prog)
{
	int		x;
	t_ray	ray;
	float	cam;
	int		lineheight;
	double	pourcent;
	t_vec2	impact;
	
	x = 0;
	while (x < prog->img_data.size.x)
	{
		cam = 2 * x / (double) prog->img_data.size.x - 1;
		set_ray(prog->player, &ray, cam);
		impact = get_impact(&ray, &prog->map);
		get_texture_from_ray(&ray);
		lineheight = prog->img_data.size.y / ray.dist_perp * 1.4;
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);
		draw_column(prog, x, pourcent, ray.side, lineheight);
		x++;
	}
}

/*
void	ray_casting_loop(t_program *prog)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	t_direction	text_dir;
	double		pourcent;
	float		height;

	height = prog->img_data.size.y / prog->fov * 95;
	x = 0;
	while (x < prog->img_data.size.x)
	{
		direction = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - prog->fov
			/ 2 + (float)x / prog->img_data.size.x * prog->fov;
		impact = get_impact_point(prog->player.pos, direction, prog->map);
		text_dir = get_text_dir(impact, prog->player.pos);
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);
		dist = vec2_dist(prog->player.pos, impact) * cos(deg_to_rad(direction)
			- vec2_to_angle(prog->player.dir_cam));
		draw_column(prog, x, pourcent, text_dir, height / dist);
		x += 1;
	}
}
*/
