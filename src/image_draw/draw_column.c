/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:14:19 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 16:32:18 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	draw_column(t_program *program, t_direction dir, float tex_pourcentage, float distance)
{
	t_texture	texture;
	int			y_text_pos;

	texture = program->map->textures[dir];
	y_text_pos = (int)(tex_pourcentage * (float)texture.size.y);
}
