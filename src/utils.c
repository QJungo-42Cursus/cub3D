/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 10:56:58 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	error_print(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
}

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
}

int	init_win(t_program *program)
{
	program->win = mlx_new_window(program->mlx, 1600, 900, (char *)"cube3D");
	if (program->win == NULL)
	{
		error_print("mlx_new_window error");
		mlx_destroy_display(program->mlx);
		free(program->mlx);
		return (ERROR);
	}
	return (SUCCESS);
}

void	free_map(t_map *map)
{
	int		i;

	if (map->textures[NORTH].pixels)
		free(map->textures[NORTH].pixels);
	if (map->textures[SOUTH].pixels)
		free(map->textures[SOUTH].pixels);
	if (map->textures[WEST].pixels)
		free(map->textures[WEST].pixels);
	if (map->textures[EAST].pixels)
		free(map->textures[EAST].pixels);

	if (map->tiles == NULL)
		return ;
	i = 0;
	while (i < map->size.y)
	{
		free(map->tiles[i]);
		i++;
	}
	free(map->tiles);
}

void	free_program(t_program *program)
{
	free_map(&program->map);
	if (program->mlx == NULL)
		return ;
	if (program->win != NULL)
		mlx_destroy_window(program->mlx, program->win);
	mlx_destroy_display(program->mlx); // TODO segfault
	free(program->mlx);
}
