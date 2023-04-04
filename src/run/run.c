/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 12:50:32 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

t_img_data img_data;

int	loop_hook(void *data)
{
	t_program *program = (t_program *)data;

	if (!program->refresh)
	{
		return 0;
	}
	fillscreen(&img_data, program->map.ceiling_color, program->map.floor_color);
	draw_minimap(program, &img_data, new_vec2i(10, 10), new_vec2(15, 15));
	mlx_put_image_to_window(program->mlx, program->win, img_data.img, 0, 0);
	printf("loop hook refresh\n");

	program->refresh = FALSE;
	return 0;
}

int	close_window(void *data)
{
	t_program *program = (t_program *)data;

	program->refresh = FALSE;
	mlx_loop_end(program->mlx);
	return 0;
}

int	key_hook(int key, void *data)
{
	t_program *program = (t_program *)data;

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
	{
		//program->player.dir += 0.1;
	}
	else if (key == KEY_LEFT)
	{
		//program->player.dir -= 0.1;
	}
	else
	{
		program->refresh = FALSE;
	}
	return 0;
}

void	run(t_program *program)
{
	mlx_do_key_autorepeaton(program->mlx);
	img_data = new_img_data(program->mlx, new_vec2i(1600, 900));
	mlx_hook(program->win, ON_DESTROY, 0, (int (*)())close_window, program);
	mlx_hook(program->win, ON_KEYDOWN, 1, (int (*)())key_hook, program);
	mlx_loop_hook(program->mlx, (int (*)())loop_hook, program);
	mlx_loop(program->mlx);
}

//LOG_TILES(program->map);
//printf("player pos : %f, %f dir : %c \n", program->player.pos.x, program->player.pos.y, program->player.dir);
