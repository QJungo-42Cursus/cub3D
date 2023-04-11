/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:06:46 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/11 13:59:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

unsigned int	color_from_rgb(unsigned char r,
					unsigned char g, unsigned char b)
{
	t_rgb				color;
	unsigned char		*ptr;

	color = 0x00000000;
	ptr = (unsigned char *)&color;
	ptr[2] = r;
	ptr[1] = g;
	ptr[0] = b;
	return (color);
}

void	color_to_rgb(t_rgb color,
			unsigned char *r, unsigned char *g, unsigned char *b)
{
	unsigned char		*ptr;

	ptr = (unsigned char *)&color;
	*r = ptr[2];
	*g = ptr[1];
	*b = ptr[0];
}
