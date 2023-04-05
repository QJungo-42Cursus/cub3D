/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/05 08:05:26 by qjungo           ###   ########.fr       */
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
		start.x += directeur.x / 100.;
		start.y += directeur.y / 100.;
	}
	return (start);
}

# define PIXEL_RATIO 1

void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	float		height = 400;

	t_vec2		perp_dir = new_vec2(-prog->player.dir_cam.y, prog->player.dir_cam.x);
	t_vec2		proj = prog->player.pos;
	proj.x += perp_dir.x * PIXEL_RATIO * prog->img_data.size.x / 2;
	proj.y += perp_dir.y * PIXEL_RATIO * prog->img_data.size.y / 2;

	x = 0;
	while (x < img_data->size.x)
	{
		direction = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - FOV
			/ 2 + (float)x / (float)img_data->size.x * FOV;
		impact = get_impact_point(prog->player.pos, direction, prog->map);
		dist = vec2_dist(prog->player.pos, impact);

		/*
		proj.x -= (perp_dir.x * PIXEL_RATIO);
		proj.y -= (perp_dir.y * PIXEL_RATIO);
		dist = vec2_dist(proj, impact);
		*/

		draw_line(new_line(new_vec2(x, img_data->size.y / 2. + height / dist),
				new_vec2 (x, img_data->size.y
					/ 2. - height / dist), C_BLUE), img_data);
		x += 1;
	}
}
