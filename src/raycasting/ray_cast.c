/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/04 17:54:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	return (tiles[coor.y][coor.x] == WALL);
}

// TODO
// - le faire sans les steps (avec round ?)
void	get_impact(t_ray *ray, t_map *map)
{
	int		hit;
	int		side;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos_tile.x += ray->step.x;
			side = FALSE;
		}
		else
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos_tile.y += ray->step.y;
			side = TRUE;
		}
		if (ray->pos_tile.x < 0 || ray->pos_tile.y < 0)
			break ;
		if (ray->pos_tile.x >= map->size.x || ray->pos_tile.y >= map->size.y)
			break ;
		if (is_a_wall(ray->pos_tile, map->tiles))
			hit = TRUE;
	}
	if (side == FALSE)
		ray->perpWalldist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perpWalldist = (ray->side_dist.y - ray->delta_dist.y);
}

static void	init_ray(t_player player, t_ray *ray)
{
	ray->pos_tile.x = (int)player.pos.x;
	ray->pos_tile.y = (int)player.pos.y;
}

void	set_ray(t_player play, t_ray *ray, t_vec2 cam)
{
	init_ray(play, ray);
	ray->dir.x = play.dir_cam.x + play.cam_plan.x * cam.x;
	ray->dir.y = play.dir_cam.y + play.cam_plan.y * cam.x;
	ray->delta_dist.x
		= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->delta_dist.y
		= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	ray->step = new_vec2(1, 1);
	ray->side_dist.x = (ray->pos_tile.x + 1 - play.pos.x) * ray->delta_dist.x;
	ray->side_dist.y = (ray->pos_tile.y + 1 - play.pos.y) * ray->delta_dist.y;

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (play.pos.x - ray->pos_tile.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (play.pos.y - ray->pos_tile.y) * ray->delta_dist.y;
	}
	ray->perpWalldist = 0;
}

void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int		x;
	t_ray	ray;
	t_vec2	cam;
	int h = 500;
	int lineHeight;

	x = 0;
	while (x < img_data->size.x)
	{
		cam.x = 2 * x / (double) img_data->size.x + 1;
		set_ray(prog->player, &ray, cam);
		get_impact(&ray, &prog->map);
		/* draw */
		lineHeight = (int)(h / ray.perpWalldist);
		draw_line(new_line(new_vec2(x, img_data->size.y / 2. + lineHeight / 2.),
			new_vec2(x, img_data->size.y / 2. - lineHeight / 2.), C_BLUE), img_data);
		x++;
	}
}
