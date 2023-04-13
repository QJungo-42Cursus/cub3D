/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:34:23 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/11 15:12:35 by qjungo           ###   ########.fr       */
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
		move_toward(&program->player, program->map, new_vec2i(1, 0));
	else if (key == KEY_D)
		move_toward(&program->player, program->map, new_vec2i(-1, 0));
	else
		return (FALSE);
	return (TRUE);
}

static int	cam_move(int key, t_program *program)
{
	if (key == KEY_RIGHT)
		rotate_cam(&program->player, 0.1);
	else if (key == KEY_LEFT)
		rotate_cam(&program->player, -0.1);
	else
		return (FALSE);
	return (TRUE);
}

static int	minimap_move(int key, t_program *program)
{
	if (key == KEY_PLUS && program->minimap_scale < 30)
		program->minimap_scale += 1;
	else if (key == KEY_MINUS && program->minimap_scale > 3)
		program->minimap_scale -= 1;
	return (TRUE);
}

int	key_hook(int key, t_program *program)
{
	t_bool		should_refresh;

	should_refresh = FALSE;
	if (key == KEY_ESC)
	{
		program->refresh = FALSE;
		free_program(program);
		exit(0);
	}
	else if (key == KEY_PLUS || key == KEY_MINUS)
		should_refresh = (t_bool)minimap_move(key, program);
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		should_refresh = (t_bool)player_move(key, program);
	else if (key == KEY_RIGHT
		|| key == KEY_LEFT || key == KEY_P || key == KEY_O)
		should_refresh = (t_bool)cam_move(key, program);
	program->refresh = should_refresh;
	return (0);
}
