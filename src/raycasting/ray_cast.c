/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/07 17:39:00 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	return (tiles[coor.y][coor.x] == WALL);
}

int	signe_2(float x)
{
	if (x < 0)
		return (-1);
	else
		return (1);
}

float	get_pourcentage(t_player player, t_ray ray)
{
	float	pourcent;
	float	hyp;
	float	adj;
	float	opp;

	if (ray.side == 1 && ray.dir.x != 0)
	{
		hyp = ray.pos_ray.x;
		if (ray.dir.x < 0)
			adj = player.pos.x - ray.pos_tile.x ;
		else
			adj = ray.pos_tile.x + 1 - player.pos.x;
		opp = sqrt(hyp * hyp - adj * adj);
		pourcent = player.pos.x + (signe_2(ray.dir.y) * opp);
		pourcent -= (int) pourcent;
	}
	else if (ray.side == 0 && ray.dir.y != 0)
	{
		hyp = ray.pos_ray.y;
		if (ray.dir.y < 0)
			adj = player.pos.y - ray.pos_tile.y ;
		else
			adj = ray.pos_tile.y + 1 - player.pos.y;
		opp = sqrt(hyp * hyp - adj * adj);
		pourcent = player.pos.y + (signe_2(ray.dir.x) * opp);
		pourcent -= (int) pourcent;
	}
	else if (ray.side == 1)
		pourcent = player.pos.y - (int) player.pos.y;
	else
		pourcent = player.pos.x - (int) player.pos.x;
	return (pourcent);
}

/*
			printf("pos_ray: %2f, %2f\n", ray->pos_ray.x, ray->pos_ray.y);
			printf("pos_ray: %d, %d\n", ray->pos_tile.x, ray->pos_tile.y);
 */
void	get_impact2(t_ray *ray, t_map *map)
{
	while (TRUE)
	{
		if (ray->pos_ray.x < ray->pos_ray.y)
		{
			ray->pos_ray.x += ray->delta_dist.x;
			ray->pos_tile.x += ray->step.x;
			ray->side = 1;
		}
		else
		{
			ray->pos_ray.y += ray->delta_dist.y;
			ray->pos_tile.y += ray->step.y;
			ray->side = 0;
		}
		if (is_a_wall(ray->pos_tile, map->tiles))
			break ;
	}
	if (ray->side == 1)
		ray->dist_perp = (ray->pos_ray.x - ray->delta_dist.x);
	else
		ray->dist_perp = (ray->pos_ray.y - ray->delta_dist.y);
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
	
	x = 0;
	printf("player: %2f,%2f\n", prog->player.pos.x, prog->player.pos.y);
	while (x < prog->img_data.size.x)
	{
		cam = 2 * x / (double) prog->img_data.size.x - 1;
		set_ray(prog->player, &ray, cam);
		get_impact2(&ray, &prog->map);
		pourcent = get_pourcentage(prog->player, ray);
		get_texture_from_ray(&ray);
		lineheight = prog->img_data.size.y / ray.dist_perp * 1.4;
		/*
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);
			*/
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
