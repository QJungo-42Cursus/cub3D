/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:40:53 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 22:15:41 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_mlx.h"
#include "../libft.h"

void	set_var(t_vec2 *e, t_vec2 *del, t_vec2 *d, t_vec2 *inc)
{
	d->x = 2 * e->x;
	d->y = 2 * e->y;
	del->x = e->x;
	del->y = e->y;
	inc->x = 1;
	inc->y = 1;
}

void	case_dx_dy(t_vec2 e, t_line line, t_img_data *data)
{
	int		i;
	t_vec2	del;
	t_vec2	d;
	t_vec2	inc;

	i = 0;
	set_var(&e, &del, &d, &inc);
	if (line.p1.x > line.p2.x)
		inc.x = -1;
	if (line.p1.y > line.p2.y)
		inc.y = -1;
	while (i <= del.x)
	{
		if (line.p1.x >= 0 && line.p1.x < data->size.x
			&& line.p1.y >= 0 && line.p1.y < data->size.y)
			pixel_to_image(data, new_vec2(line.p1.x, line.p1.y), line.color);
		i++;
		line.p1.x += inc.x;
		e.x -= d.y;
		if (e.x < 0)
		{
			line.p1.y += inc.y;
			e.x += d.x;
		}
	}
}

void	case_dy_dx(t_vec2 e, t_line line, t_img_data *data)
{
	int		i;
	t_vec2	del;
	t_vec2	d;
	t_vec2	inc;

	i = 0;
	set_var(&e, &del, &d, &inc);
	if (line.p1.x > line.p2.x)
		inc.x = -1;
	if (line.p1.y > line.p2.y)
		inc.y = -1;
	while (i <= del.y)
	{
		if (line.p1.x >= 0 && line.p1.x < data->size.x
			&& line.p1.y >= 0 && line.p1.y < data->size.y)
			pixel_to_image(data, new_vec2(line.p1.x, line.p1.y), line.color);
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
		case_dx_dy(e, line, img_data);
	else if (e.y > e.x)
		case_dy_dx(e, line, img_data);
}
