/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:26:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/12 21:06:30 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	draw_ceiling(t_program *prog, int x, int img_y)
{
	int		y;

	y = 0;
	while (y < img_y)
	{
		pixel_to_image(&prog->img_data,
			new_vec2(x, y), prog->map.ceiling_color);
		y++;
	}
}

static void	draw_floor(t_program *prog, int x, int img_y)
{
	while (img_y < prog->img_data.size.y)
	{
		pixel_to_image(&prog->img_data,
			new_vec2(x, img_y), prog->map.floor_color);
		img_y++;
	}
}

// only for norm ...
static int	texture_x(double text_pourcentage, t_texture texture)
{
	return ((int)(text_pourcentage * (double)texture.size.x));
}

void	draw_column(t_program *prog, int x, double *tab, t_direction text_dir)
{
	int			img_y;
	t_texture	texture;
	double		texture_y;

	texture_y = 0;
	texture = prog->map.textures[text_dir];
	img_y = prog->img_data.size.y / 2. - tab[1] / 2.;
	if (img_y < 0)
	{
		texture_y = (float)texture.size.y / tab[1] * -img_y;
		img_y = 0;
	}
	else
		draw_ceiling(prog, x, img_y);
	while (img_y < prog->img_data.size.y / 2. + tab[1] / 2)
	{
		if (img_y >= prog->img_data.size.y || texture_y + 1 >= texture.size.y)
			break ;
		pixel_to_image(&prog->img_data, new_vec2(x, img_y), texture.pixels[
			texture_x(tab[0], texture)
			+ (int)(texture_y)*(texture.size.y)]);
		texture_y += (float)texture.size.y / tab[1];
		img_y++;
	}
	draw_floor(prog, x, img_y);
}
