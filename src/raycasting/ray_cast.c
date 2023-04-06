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
}

void	get_impact(t_ray *ray, t_map *map)
{
	int		hit;

	hit = FALSE;
	while (hit == FALSE)
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
			hit = TRUE;
	}
	if (ray->side == 1)
		ray->dist_perp = (ray->pos_ray.x - ray->delta_dist.x);
	else
		ray->dist_perp = (ray->pos_ray.y - ray->delta_dist.y);
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

void	ray_casting_loop2(t_program *prog)
{
	int		x;
	t_ray	ray;
	float	cam;
	int		lineheight;
	
	x = 0;
	while (x < prog->img_data.size.x)
	{
		cam = 2 * x / (double) prog->img_data.size.x - 1;
		set_ray(prog->player, &ray, cam);
		get_impact(&ray, &prog->map);
		get_texture_from_ray(&ray);
		lineheight = (int)(((float)prog->img_data.size.y / 2) / ray.dist_perp);
		if (ray.side == 0)
			draw_line(new_line(new_vec2(x, prog->img_data.size.y / 2. + lineheight / 2.),
			new_vec2(x, prog->img_data.size.y / 2. - lineheight / 2.), C_RED), &prog->img_data);
		else if (ray.side == 1)
			draw_line(new_line(new_vec2(x, prog->img_data.size.y / 2. + lineheight / 2.),
			new_vec2(x, prog->img_data.size.y / 2. - lineheight / 2.), C_GREEN), &prog->img_data);
		else if (ray.side == 2)
			draw_line(new_line(new_vec2(x, prog->img_data.size.y / 2. + lineheight / 2.),
			new_vec2(x, prog->img_data.size.y / 2. - lineheight / 2.), C_BLUE), &prog->img_data);
		else if (ray.side == 3)
			draw_line(new_line(new_vec2(x, prog->img_data.size.y / 2. + lineheight / 2.),
			new_vec2(x, prog->img_data.size.y / 2. - lineheight / 2.), C_BLACK), &prog->img_data);
		x++;
	}
}

