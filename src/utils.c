/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/11 14:46:11 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

#include <errno.h>
#include <string.h>

void	error_print(const char *msg)
{
	printf("Error\n%s\n", msg);
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
	free(program->mlx);
}

t_bool	is_in_map(t_vec2 pos, t_map map)
{
	return ((t_bool)(pos.x >= 0 && pos.x < map.size.x
		&& pos.y >= 0 && pos.y < map.size.y));
}

#include <sys/time.h>
long	get_time(void)
{
	// TODO remove this function
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
