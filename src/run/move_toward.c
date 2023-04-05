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

static t_vec2	get_new_pos(t_vec2 actual, t_vec2 dir)
{
	return (new_vec2(actual.x + dir.x, actual.y + dir.y));
}

void	move_toward(t_player *player, t_map map, t_vec2i dir)
{
	t_vec2	new_pos;

	new_pos = get_new_pos(player->pos, new_vec2(dir.x, dir.y));
	if (map.tiles[(int)new_pos.y][(int)new_pos.x] == FLOOR)
		player->pos = new_pos;
}
