/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 23:51:00 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	error_print(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
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
	mlx_destroy_display(program->mlx);
	free(program->mlx);
}

t_bool	is_in_map(t_vec2 pos, t_map map)
{
	return ((t_bool)(pos.x >= 0 && pos.x < map.size.x
		&& pos.y >= 0 && pos.y < map.size.y));
}
