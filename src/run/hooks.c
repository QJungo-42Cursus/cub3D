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

#include "../cub3D.h"
#include <math.h>

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

static void	rotate_cam(t_player *player, double angle)
{
	double	old_dir_cam;
	double	old_cam_planx;

	old_dir_cam = player->dir_cam.x;
	player->dir_cam.x = player->dir_cam.x * cos(angle)
		- player->dir_cam.y * sin(angle);
	player->dir_cam.y = old_dir_cam * sin(angle)
		+ player->dir_cam.y * cos(angle);
	old_cam_planx = player->cam_plan.x;
	player->cam_plan.x = player->cam_plan.x * cos(angle)
		- player->cam_plan.y * sin(angle);
	player->cam_plan.y = old_cam_planx * sin(angle)
		+ player->cam_plan.y * cos(angle);
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
