/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:27:36 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 20:42:33 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

t_line	new_line(t_vec2 a, t_vec2 b, t_rgb color)
{
	t_line	line;

	line.p1 = a;
	line.p2 = b;
	line.color = color;
	return (line);
}
