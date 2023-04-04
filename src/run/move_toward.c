/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toward.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:42:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 12:53:44 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube3D.h"

void	move_toward(t_player *player, t_map map, t_vec2i dir)
{
	t_vec2	new_pos;
	float	speed;

	speed = 0.1;
	new_pos = new_vec2(player->pos.x + dir.x, player->pos.y + dir.y);
	if (map.tiles[(int)new_pos.y][(int)new_pos.x] == FLOOR)
	{
		player->pos = new_vec2(player->pos.x + dir.x * speed,
			player->pos.y + dir.y * speed);
	}
}
