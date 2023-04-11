/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_set_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:14:07 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/07 15:39:57 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

static void	init_ray(t_ray *ray)
{
	ray->side = 0;
	ray->dist_perp = 0;
	ray->delta_dist.x = INFINITY;
	ray->delta_dist.y = INFINITY;
	ray->step = new_vec2(1, 1);
}

void	set_ray(t_player play, t_ray *ray, float cam)
{
	ray->pos_tile.x = (int)play.pos.x;
	ray->pos_tile.y = (int)play.pos.y;
	ray->dir.x = play.dir_cam.x + play.cam_plan.x * cam;
	ray->dir.y = play.dir_cam.y + play.cam_plan.y * cam;
	init_ray(ray);
	if (ray->dir.x != 0)
		ray->delta_dist.x
			= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	if (ray->dir.y != 0)
		ray->delta_dist.y
			= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
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
