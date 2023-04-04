/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 11:25:37 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

int	loop_hook(void *data)
{
	t_program *program = (t_program *)data;

	if (!program->refresh)
		return 0;
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

	printf("%d\n", key);
	printf("key esc = %d\n", KEY_ESC);
	if (key == KEY_ESC)
	{
		program->refresh = FALSE;
		mlx_loop_end(program->mlx);
	}
	/*
	else if (key == KEY_W)
	{
		program->player->pos.x += 0.1;
		program->player->pos.y += 0.1;
		program->refresh = TRUE;
	}
	else if (key == KEY_S)
	{
		program->player->pos.x -= 0.1;
		program->player->pos.y -= 0.1;
		program->refresh = TRUE;
	}
	else if (key == KEY_A)
	{
		program->player->pos.x -= 0.1;
		program->player->pos.y += 0.1;
		program->refresh = TRUE;
	}
	else if (key == KEY_D)
	{
		program->player->pos.x += 0.1;
		program->player->pos.y -= 0.1;
		program->refresh = TRUE;
	}
	else if (key == KEY_RIGHT)
	{
		program->player->angle += 0.1;
		program->refresh = TRUE;
	}
	else if (key == KEY_LEFT)
	{
		program->player->angle -= 0.1;
		program->refresh = TRUE;
	}
	*/
	return 0;
}

void	run(t_program *program)
{
	mlx_do_key_autorepeaton(program->mlx);
	mlx_hook(program->win, ON_DESTROY, 0, close_window, program);
	mlx_hook(program->win, ON_KEYDOWN, 1L<<0, key_hook, program);

	mlx_loop_hook(program->mlx, loop_hook, program);
	mlx_loop(program->mlx);
	printf("close window\n");
}
