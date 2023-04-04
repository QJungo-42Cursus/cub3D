/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:05:12 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 18:10:54 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cube3D.h"
#include <math.h>

static void	draw_player(t_img_data *img_data, t_vec2i start, t_vec2 size, t_vec2 player_pos)
{
	draw_rect(new_rect(new_vec2(player_pos.x * size.x + start.x,
			player_pos.y * size.y + start.y), new_vec2(5, 5), C_RED), img_data);
}

static void	draw_rayons(t_program *prog, t_img_data *img_data, t_vec2i start, t_vec2 size)
{
	int		x;
	t_ray	ray;
	t_vec2	cam;
	//int		fov = 90;

	x = 0;
	while (x < img_data->size.x)
	{
		cam.x = 2 * x / (double) img_data->size.x + 1;
		set_ray(prog->player, &ray, cam);
		get_impact(&ray, &prog->map);
		draw_line(new_line(
					new_vec2(prog->player.pos.x * size.x + start.x,	prog->player.pos.y * size.y + start.y),
					new_vec2((ray.side_dist.x + prog->player.pos.x) * size.x + start.x, (ray.side_dist.y + prog->player.pos.y) * size.y + start.y),
					C_BLUE), img_data);
		/* draw */
		x++;
	}
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
	draw_rayons(program, img_data, start, size);
}
