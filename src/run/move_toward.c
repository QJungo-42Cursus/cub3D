/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toward.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:42:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/12 13:36:06 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#define SPEED 0.3

static t_vec2	get_new_pos(t_vec2 actual, t_vec2 dir)
{
	return (new_vec2(actual.x + dir.x * SPEED, actual.y + dir.y * SPEED));
}

void	move_toward(t_player *player, t_map map, t_vec2i dir)
{
	t_vec2		new_pos;
	float		cam_angle;
	float		dir_angle;
	float		angle;

	cam_angle = vec2_to_angle(player->dir_cam) - deg_to_rad(90);
	dir_angle = vec2_to_angle(new_vec2(dir.x, dir.y));
	angle = cam_angle - dir_angle;
	new_pos = get_new_pos(player->pos, angle_to_vec2(angle));
	if (map.tiles[(int)new_pos.y][(int)new_pos.x] == FLOOR)
		player->pos = new_pos;
}
