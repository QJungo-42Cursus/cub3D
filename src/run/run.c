/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/05 19:54:22 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	loop_hook(t_program *program)
{
	if (!program->refresh)
		return (0);
	fillscreen(&program->img_data,
		program->map.ceiling_color, program->map.floor_color);
	ray_casting_loop2(program);
	//ray_casting_loop(program);
	draw_minimap(program, &program->img_data, new_vec2i(10, 10), MINIMAP_SCALE);
	mlx_put_image_to_window(program->mlx,
		program->win, program->img_data.img, 0, 0);
	program->refresh = FALSE;
	return (0);
}

static int	close_window(t_program *program)
{
	program->refresh = FALSE;
	mlx_loop_end(program->mlx);
	return (0);
}

void	run(t_program *program)
{
	mlx_do_key_autorepeaton(program->mlx);
	program->img_data = new_img_data(program->mlx, new_vec2i(X_SIZE, Y_SIZE));
	mlx_hook(program->win, ON_DESTROY, 0, (int (*)())close_window, program);
	mlx_hook(program->win, ON_KEYDOWN, 1, (int (*)())key_hook, program);
	mlx_loop_hook(program->mlx, (int (*)())loop_hook, program);
	mlx_loop(program->mlx);
	mlx_destroy_image(program->mlx, program->img_data.img);
}
