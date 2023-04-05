/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_impact_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:57:36 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/05 17:57:39 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

t_vec2	get_impact_point(t_vec2 start, float direction, t_map map)
{
	t_vec2		directeur;

	directeur = angle_to_vec2(deg_to_rad(direction));
	while (is_in_map(start, map)
		&& !(map.tiles[(int)start.y][(int)start.x] != FLOOR))
	{
		start.x += directeur.x / 1000.;
		start.y += directeur.y / 1000.;
	}
	return (start);
}
