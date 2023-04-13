/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/12 21:08:01 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <math.h>

static float	get_pourcent(t_vec2 player_pos, t_ray ray)
{
	float	pourcent;
	t_vec2	impact;

	if (ray.side == 1)
	{
		impact.y = player_pos.y + ray.dist_final * (ray.dir.y
				* (1 / sqrt (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y)));
		pourcent = impact.y - ray.pos_tile.y;
	}
	else
	{
		impact.x = player_pos.x + ray.dist_final * (ray.dir.x
				* (1 / sqrt (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y)));
		pourcent = impact.x - ray.pos_tile.x;
	}
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
		if (map->tiles[ray->pos_tile.y][ray->pos_tile.x] == WALL)
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
	double	tab[2];

	x = 0;
	while (x < prog->img_data.size.x)
	{
		cam = 2 * x / (double) prog->img_data.size.x - 1;
		ray.dir.x = prog->player.dir_cam.x + prog->player.cam_plan.x * cam;
		ray.dir.y = prog->player.dir_cam.y + prog->player.cam_plan.y * cam;
		set_ray(prog->player.pos, &ray);
		get_impact2(&ray, &prog->map);
		tab[0] = get_pourcent(prog->player.pos, ray);
		get_texture_from_ray(&ray);
		ray.dist_perp = ray.dist_final * cos(vec2_to_angle(ray.dir)
				- vec2_to_angle(prog->player.dir_cam));
		tab[1] = prog->img_data.size.y / ray.dist_perp * 1.34;
		draw_column(prog, x, tab, ray.side);
		x++;
	}
}
