/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:26:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/05 13:02:47 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	draw_column(t_program *prog, int x, double text_pourcentage,
			t_direction text_dir, double height)
{
	int			img_y;
	t_texture	texture;
	int			texture_x;
	double		texture_y;

	texture_y = 0;
	texture = prog->map.textures[text_dir];
	img_y = prog->img_data.size.y / 2. - height / 2.;
	texture_x = (int)(text_pourcentage * (double)texture.size.x);
	while (img_y < prog->img_data.size.y / 2. + height / 2)
	{
		if (!(img_y < 0 || img_y >= prog->img_data.size.y)
			&& texture_y + 1 < texture.size.y)
			pixel_to_image(&prog->img_data, new_vec2(x, img_y), texture.pixels[
				texture_x + (int)(texture_y)*(texture.size.y)]);
		texture_y += (float)texture.size.y / height;
		img_y++;
	}
}
