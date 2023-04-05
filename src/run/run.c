/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/05 11:43:32 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	loop_hook(void *data)
{
	t_program	*program;

	program = (t_program *)data;
	if (!program->refresh)
		return (0);
	fillscreen(&program->img_data,
		program->map.ceiling_color, program->map.floor_color);
	ray_casting_loop(program);
	draw_minimap(program, &program->img_data, new_vec2i(10, 10), MINIMAP_SCALE);
	mlx_put_image_to_window(program->mlx,
		program->win, program->img_data.img, 0, 0);
	program->refresh = FALSE;
	return (0);
}

int	close_window(void *data)
{
	t_program	*program;

	program = (t_program *)data;
	program->refresh = FALSE;
	mlx_loop_end(program->mlx);
	return (0);
}

int	key_hook(int key, void *data)
{
	t_program	*program;

	program = (t_program *)data;
	program->refresh = TRUE;
	if (key == KEY_ESC)
	{
		program->refresh = FALSE;
		mlx_loop_end(program->mlx);
	}
	else if (key == KEY_W)
		move_toward(&program->player, program->map, new_vec2i(0, -1));
	else if (key == KEY_S)
		move_toward(&program->player, program->map, new_vec2i(0, 1));
	else if (key == KEY_A)
		move_toward(&program->player, program->map, new_vec2i(-1, 0));
	else if (key == KEY_D)
		move_toward(&program->player, program->map, new_vec2i(1, 0));
	else if (key == KEY_RIGHT)
		rotate_cam(&program->player, 0.1);
	else if (key == KEY_LEFT)
		rotate_cam(&program->player, -0.1);
	else if (key == KEY_P && program->fov < 95)
		program->fov += 5;
	else if (key == KEY_O && program->fov > 30)
		program->fov -= 5;
	else
		program->refresh = FALSE;
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
