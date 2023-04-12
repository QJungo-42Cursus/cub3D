/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:50:07 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/12 13:15:24 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

void	draw_rect(t_rect rect, t_img_data *img_data)
{
	int			x;
	int			y;

	y = rect.position.y;
	while (y < rect.position.y + rect.size.y)
	{
		if (y >= img_data->size.y)
			break ;
		x = rect.position.x;
		while (x < rect.position.x + rect.size.x)
		{
			if (x >= img_data->size.x)
				break ;
			pixel_to_image(img_data, new_vec2(x, y), rect.color);
			x++;
		}
		y++;
	}
}

t_rect	new_rect(t_vec2 position, t_vec2 size, int color)
{
	t_rect		rect;

	rect.position = position;
	rect.size = size;
	rect.color = color;
	return (rect);
}
