/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 10:32:20 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 15:41:50 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "mlx.h"
#include <math.h>

static int	get_img(void *mlx,
		char *text_path, t_texture *text, t_img_data *img_data)
{
	void		*img_ptr;

	img_ptr = mlx_xpm_file_to_image(mlx, text_path,
			&text->size.x, &text->size.y);
	if (img_ptr == NULL)
		return (ERROR);
	*img_data = img_data_from(img_ptr);
	text->pixels
		= malloc(sizeof(unsigned int) * text->size.x * text->size.y);
	if (text->pixels == NULL)
		return (ERROR);
	return (SUCCESS);
}

t_texture	new_text(void *mlx, char *text_path)
{
	t_texture	text;
	t_vec2i		i;
	t_img_data	img_data;
	int			addr;

	text.pixels = NULL;
	if (get_img(mlx, text_path, &text, &img_data) == ERROR)
		return (text);
	i.x = 0;
	while (i.x < text.size.x)
	{
		i.y = 0;
		while (i.y < text.size.y)
		{
			addr = (i.y * img_data.line_length) + i.x * (img_data.bpp / 8);
			text.pixels[i.x + i.y * text.size.y]
				= *(unsigned int*)&img_data.addr[addr];
			i.y++;
		}
		i.x++;
	}
	mlx_destroy_image(mlx, img_data.img);
	return (text);
}
