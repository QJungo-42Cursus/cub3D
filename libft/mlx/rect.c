/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:50:07 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 09:51:47 by qjungo           ###   ########.fr       */
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
		x = rect.position.x;
		while (x < rect.position.x + rect.size.x)
		{
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
