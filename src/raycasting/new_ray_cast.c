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
		start.x += directeur.x / 1000.;
		start.y += directeur.y / 1000.;
	}
	return (start);
}

# define PIXEL_RATIO 1

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

void	draw_column(t_program *prog, int x, double text_pourcentage, t_direction text_dir, double height)
{
	int			img_y;
	t_texture	texture;

	texture = prog->map.textures[text_dir];
	img_y = prog->img_data.size.y / 2. - height / 2.;
	while (img_y < prog->img_data.size.y / 2. + height / 2)
	{
		if (!(img_y < 0 || img_y >= prog->img_data.size.y))
			pixel_to_image(&prog->img_data, new_vec2(x, img_y), texture.pixels[
				(int)(text_pourcentage * texture.size.x) +
				(int)(img_y / prog->img_data.size.y * texture.size.y)]);
		img_y++;
	}
}

void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int			x;
	float		dist;
	t_vec2		impact;
	float		direction;
	float		height = 400;
	t_direction	text_dir;
	double		pourcent;

	x = 0;
	while (x < img_data->size.x)
	{
		direction = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - FOV
			/ 2 + (float)x / (float)img_data->size.x * FOV;
		impact = get_impact_point(prog->player.pos, direction, prog->map);

		text_dir = get_text_dir(impact, prog->player.pos);
		if (is_x_collision(impact))
			pourcent = abs_diff_with_int(impact.y);
		else
			pourcent = abs_diff_with_int(impact.x);

		dist = vec2_dist(prog->player.pos, impact);

		draw_column(prog, x, pourcent, text_dir, height / dist);
		x += 1;
	}
}
