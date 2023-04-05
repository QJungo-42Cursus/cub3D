/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toward.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:42:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 23:44:27 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#define SPEED 0.1

static t_vec2	get_new_pos(t_vec2 actual, t_vec2 dir)
{
	return (new_vec2(actual.x + dir.x * SPEED, actual.y + dir.y * SPEED));
}


void	move_toward(t_player *player, t_map map, t_vec2i dir)
{
	t_vec2	new_pos;

	float cam_angle = vec2_to_angle(player->dir_cam) - deg_to_rad(90);
	float dir_angle = vec2_to_angle(new_vec2(dir.x, dir.y));
	float angle = cam_angle - dir_angle;
	new_pos = get_new_pos(player->pos, angle_to_vec2(angle));
	(void)dir;
	//new_pos = get_new_pos(player->pos, new_vec2(dir.x, dir.y));
	if (map.tiles[(int)new_pos.y][(int)new_pos.x] == FLOOR)
		player->pos = new_pos;
}
