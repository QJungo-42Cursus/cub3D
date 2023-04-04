/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:40:53 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 17:31:51 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_mlx.h"
#include "../libft.h"

static void	case_x_to_y(t_line line, t_vec2 e, t_img_data *img_data)
{
	t_vec2	del;
	t_vec2	d;
	t_vec2	inc;
	int		i;

	d = new_vec2(2 * e.x, 2 * e.y);
	del = e;
	inc = new_vec2(1, 1);
	if (line.p1.x > line.p2.x)
		inc.x = -1;
	if (line.p1.y > line.p2.y)
		inc.y = -1;
	i = 0;
	while (i <= del.y)
	{
		if (line.p1.y > img_data->size.y || line.p1.y < 0 || line.p1.x > img_data->size.x || line.p1.x < 0)
			break ;
		pixel_to_image(img_data, line.p1, line.color);
		i++;
		line.p1.y += inc.y;
		e.y -= d.x;
		if (e.y < 0)
		{
			line.p1.x += inc.x;
			e.y += d.y;
		}
	}
}

static void	case_y_to_x(t_line line, t_vec2 e, t_img_data *img_data)
{
	t_vec2	del;
	t_vec2	d;
	t_vec2	inc;
	int		i;

	d = new_vec2(2 * e.x, 2 * e.y);
	del = e;
	inc = new_vec2(1, 1);
	if (line.p1.x > line.p2.x)
		inc.x = -1;
	if (line.p1.y > line.p2.y)
		inc.y = -1;
	i = 0;
	while (i <= del.y)
	{
		if (line.p1.y > img_data->size.y || line.p1.y < 0 || line.p1.x > img_data->size.x || line.p1.x < 0)
			break ;
		pixel_to_image(img_data, line.p1, line.color);
		i++;
		line.p1.y += inc.y;
		e.y -= d.x;
		if (e.y < 0)
		{
			line.p1.x += inc.x;
			e.y += d.y;
		}
	}
}

void	draw_line(t_line line, t_img_data *img_data)
{
	t_vec2	e;

	e.x = abs((int) line.p2.x - (int) line.p1.x);
	e.y = abs((int) line.p2.y - (int) line.p1.y);
	if (e.x > e.y)
		case_x_to_y(line, e, img_data);
	else
		case_y_to_x(line, e, img_data);
}
