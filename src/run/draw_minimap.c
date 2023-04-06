/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:05:12 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 23:48:43 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/cube3D.h"
#include <math.h>

static void	draw_rayons(t_program *prog, t_img_data *img_data,
			t_vec2i start, int scale)
{
	float		dir;
	t_vec2		impact;
	t_rgb		color;

	color = color_from_rgb(0, 0, 255);
	dir = rad_to_deg(vec2_to_angle(prog->player.dir_cam)) - prog->fov / 2;
	while (dir <= rad_to_deg(vec2_to_angle(prog->player.dir_cam))
		+ prog->fov / 2 + 1)
	{
		impact = get_impact_point(prog->player.pos, dir, prog->map);
		draw_line(new_line(new_vec2(prog->player.pos.x * scale + start.x,
					prog->player.pos.y * scale + start.y), new_vec2(impact.x
					* scale + start.x, impact.y * scale + start.y), color),
			img_data);
		dir += prog->fov / 6;
	}
}

static void	draw_player(t_img_data *img_data,
			t_vec2i start, int scale, t_vec2 player_pos)
{
	t_vec2		size;
	t_rgb		color;

	color = color_from_rgb(0, 0, 255);
	size = new_vec2(5, 5);
	draw_rect(new_rect(new_vec2(player_pos.x * scale + start.x - size.x / 2,
				player_pos.y * scale + start.y - size.y / 2), size, color),
		img_data);
}

void	draw_minimap(t_program *program,
			t_img_data *img_data, t_vec2i start, int scale)
{
	t_vec2i	index;

	index.y = 0;
	while (index.y < program->map.size.y)
	{
		index.x = 0;
		while (index.x < program->map.size.x)
		{
			if (program->map.tiles[index.y][index.x] == WALL)
				draw_rect(new_rect(new_vec2(index.x * scale + start.x,
							index.y * scale + start.y),
						new_vec2(scale, scale), program->map.floor_color),
					img_data);
			index.x++;
		}
		index.y++;
	}
	draw_player(img_data, start, scale, program->player.pos);
	draw_rayons(program, img_data, start, scale);
}
