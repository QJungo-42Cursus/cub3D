/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/04 23:48:51 by qjungo           ###   ########.fr       */
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

void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	float		height;

	height = 400;
	x = 0;
	while (x < img_data->size.x)
	{
		direction = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - FOV
			/ 2 + (float)x / (float)img_data->size.x * FOV;
		impact = get_impact_point(prog->player.pos, direction, prog->map);
		dist = vec2_dist(prog->player.pos, impact);
		draw_line(new_line(new_vec2(x, img_data->size.y / 2. + height / dist),
				new_vec2 (x, img_data->size.y
					/ 2. - height / dist), C_BLUE), img_data);
		x += 1;
	}
}
