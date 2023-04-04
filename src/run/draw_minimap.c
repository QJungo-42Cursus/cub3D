/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:05:12 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 12:59:39 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cube3D.h"
#include <math.h>

static void	draw_player(t_img_data *img_data, t_vec2i start, t_vec2 size, t_vec2 player_pos)
{
	draw_rect(new_rect(new_vec2(player_pos.x * size.x + start.x,
			player_pos.y * size.y + start.y), new_vec2(5, 5), C_RED), img_data);
}

void	draw_minimap(t_program *program,
			t_img_data *img_data, t_vec2i start, t_vec2 size)
{
	t_vec2i	index;
	t_rgb	color;

	index.y = 0;
	while (index.y < program->map.size.y)
	{
		index.x = 0;
		while (index.x < program->map.size.x)
		{
			color = C_BLACK;
			if (program->map.tiles[index.y][index.x] == FLOOR)
				color = C_GREEN;
			if (program->map.tiles[index.y][index.x] != VOID)
				draw_rect(new_rect(new_vec2(index.x * size.x + start.x,
					index.y * size.y + start.y), size, color), img_data);
			index.x++;
		}
		index.y++;
	}
	draw_player(img_data, start, size, program->player.pos);
}
