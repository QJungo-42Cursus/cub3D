/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:34:23 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/06 09:46:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	player_move(int key, t_program *program)
{
	if (key == KEY_W)
		move_toward(&program->player, program->map, new_vec2i(0, -1));
	else if (key == KEY_S)
		move_toward(&program->player, program->map, new_vec2i(0, 1));
	else if (key == KEY_A)
		move_toward(&program->player, program->map, new_vec2i(-1, 0));
	else if (key == KEY_D)
		move_toward(&program->player, program->map, new_vec2i(1, 0));
	else
		return (FALSE);
	return (TRUE);
}

static int	cam_move(t_program *program, int key)
{
	if (key == KEY_RIGHT)
		rotate_cam(&program->player, 0.1);
	else if (key == KEY_LEFT)
		rotate_cam(&program->player, -0.1);
	else if (key == KEY_P && program->fov < 95)
		program->fov += 5;
	else if (key == KEY_O && program->fov > 30)
		program->fov -= 5;
	else
		return (FALSE);
	return (TRUE);
}

int	key_hook(int key, t_program *program)
{
	t_bool		should_refresh;

	should_refresh = FALSE;
	if (key == KEY_ESC)
	{
		program->refresh = FALSE;
		mlx_loop_end(program->mlx);
	}
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		should_refresh = (t_bool)player_move(key, program);
	else if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_P || key == KEY_O)
		should_refresh = (t_bool)cam_move(program, key);
	program->refresh = should_refresh;
	return (0);
}
