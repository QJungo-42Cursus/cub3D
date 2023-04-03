/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:58:18 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 14:33:46 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	fillscreen(t_img_data *img_data, t_rgb ceiling_color, t_rgb floor_color)
{
	int		x;
	int		y;

	x = 10;
	while (x < img_data->size.x)
	{
		y = 10;
		while (y < img_data->size.y)
		{
			*(pixel_addr(x, y, img_data)) = floor_color;
			if (y < img_data->size.y / 2)
				*(pixel_addr(x, y, img_data)) = ceiling_color;
			y++;
		}
		x++;
	}
}
