/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/11 19:53:33 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	return (tiles[coor.y][coor.x] == WALL);
}

static float	get_pourcent(t_vec2 player_pos, t_ray ray)
{
	float	pourcent;
	float	norm;
	t_vec2	impact;

	norm = 1 / sqrt (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
	impact.x = player_pos.x + ray.dist_final * (ray.dir.x * norm);
	impact.y = player_pos.y + ray.dist_final * (ray.dir.y * norm);
	if (ray.side == 1)
		pourcent = impact.y - ray.pos_tile.y;
	else
		pourcent = impact.x - ray.pos_tile.x;
	return (pourcent);
}

void	get_impact2(t_ray *ray, t_map *map)
{
	while (TRUE)
	{
		if (ray->dist_next.x < ray->dist_next.y)
		{
			ray->dist_next.x += ray->delta_dist.x;
			ray->pos_tile.x += ray->step.x;
			ray->side = 1;
		}
		else
		{
			ray->dist_next.y += ray->delta_dist.y;
			ray->pos_tile.y += ray->step.y;
			ray->side = 0;
		}
		if (is_a_wall(ray->pos_tile, map->tiles))
			break ;
	}
	if (ray->side == 1)
		ray->dist_final = (ray->dist_next.x - ray->delta_dist.x);
	else
		ray->dist_final = (ray->dist_next.y - ray->delta_dist.y);
}

void	ray_casting_loop(t_program *prog)
{
	int		x;
	t_ray	ray;
	float	cam;
	int		lineheight;
	double	pourcent;

	x = 0;
	while (x < prog->img_data.size.x)
	{
		cam = 2 * x / (double) prog->img_data.size.x - 1;
		ray.pos_tile.x = (int)prog->player.pos.x;
		ray.pos_tile.y = (int)prog->player.pos.y;
		ray.dir.x = prog->player.dir_cam.x + prog->player.cam_plan.x * cam;
		ray.dir.y = prog->player.dir_cam.y + prog->player.cam_plan.y * cam;
		set_ray(prog->player.pos, &ray);
		get_impact2(&ray, &prog->map);
		pourcent = get_pourcent(prog->player.pos, ray);
		get_texture_from_ray(&ray);
		lineheight = prog->img_data.size.y / ray.dist_final * 1.4;
		draw_column(prog, x, pourcent, ray.side, lineheight);
		x++;
	}
}
