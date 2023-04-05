/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/05 13:45:41 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

double	abs_diff_with_int(double a)
{
	return (fabs(roundf(a) - a));
}

t_bool	is_x_collision(t_vec2 impact)
{
	return ((t_bool)(abs_diff_with_int(impact.x) < abs_diff_with_int(impact.y)));
}

t_direction get_text_dir(t_vec2 impact, t_vec2 player_pos)
{
	if (is_x_collision(impact))
	{
		if (impact.x > player_pos.x)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (impact.y > player_pos.y)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	ray_casting_loop(t_program *prog)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	t_direction	text_dir;
	double		pourcent;
	float		height;

	height = prog->img_data.size.y / prog->fov * 100;
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
