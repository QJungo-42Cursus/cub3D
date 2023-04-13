/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_set_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:14:07 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/11 19:53:02 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <math.h>

void	set_ray(t_vec2 play_pos, t_ray *ray)
{
	ray->side = 0;
	ray->dist_final = 0;
	ray->delta_dist.x = INFINITY;
	ray->delta_dist.y = INFINITY;
	ray->step = new_vec2(1, 1);
	ray->pos_tile.x = (int)play_pos.x;
	ray->pos_tile.y = (int)play_pos.y;
	if (ray->dir.x != 0)
		ray->delta_dist.x
			= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	if (ray->dir.y != 0)
		ray->delta_dist.y
			= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	ray->dist_next.x = (ray->pos_tile.x + 1.0 - play_pos.x) * ray->delta_dist.x;
	ray->dist_next.y = (ray->pos_tile.y + 1.0 - play_pos.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist_next.x = (play_pos.x - ray->pos_tile.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist_next.y = (play_pos.y - ray->pos_tile.y) * ray->delta_dist.y;
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
