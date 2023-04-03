/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 10:41:00 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/02 10:58:41 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "mlx.h"

t_img_data	new_img_data(void *mlx, t_vec2i size)
{
	t_img_data	img;

	img.img = mlx_new_image(mlx, size.x, size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_length, &img.endian);
	img.size = new_vec2i(size.x, size.y);
	return (img);
}

t_img_data	img_data_from(void *img)
{
	t_img_data	img_data;

	img_data.img = img;
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.line_length, &img_data.endian);
	return (img_data);
}
