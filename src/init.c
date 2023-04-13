/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:46:10 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/11 15:08:26 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_map(t_map *map)
{
	map->textures[NORTH].pixels = NULL;
	map->textures[SOUTH].pixels = NULL;
	map->textures[WEST].pixels = NULL;
	map->textures[EAST].pixels = NULL;
	map->tiles = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->ceiling_color = 0xFF000000;
	map->floor_color = 0xFF000000;
}

void	set_player_cam(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_cam = new_vec2(0, -1);
		player->cam_plan.x = 0.66;
		player->cam_plan.y = 0;
	}
	else if (c == 'S')
	{
		player->dir_cam = new_vec2(0, 1);
		player->cam_plan.x = -0.66;
		player->cam_plan.y = 0;
	}
	else if (c == 'E')
	{
		player->dir_cam = new_vec2(1, 0);
		player->cam_plan.x = 0;
		player->cam_plan.y = 0.66;
	}
	else
	{
		player->dir_cam = new_vec2(-1, 0);
		player->cam_plan.x = 0;
		player->cam_plan.y = -0.66;
	}
}

void	init_program(t_program *program)
{
	program->mlx = mlx_init();
	if (program->mlx == NULL)
	{
		error_print("mlx_init error");
		exit(1);
	}
	program->win = NULL;
	init_map(&(program->map));
	program->refresh = TRUE;
	program->minimap_scale = MINIMAP_SCALE;
}

int	init_win(t_program *program)
{
	program->win = mlx_new_window(program->mlx,
			X_SIZE, Y_SIZE, (char *)"cub3D");
	if (program->win == NULL)
	{
		error_print("mlx_new_window error");
		free(program->mlx);
		return (ERROR);
	}
	return (SUCCESS);
}
