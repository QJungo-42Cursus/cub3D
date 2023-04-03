/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 16:08:46 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	error_print(const char *msg)
{
	static int	first = TRUE;

	if (!first)
		return ;
	first = FALSE;
	ft_printf("Error\n%s\n", msg);
}

/*
void	free_text(t_texture *texture)
{
	int		i;
	if (texture->pixels == NULL)
		return ;
	i = 0;
	while (i < texture->size.y)
	{
		free(texture->pixels[i]);
		i++;
	}
	free(texture->pixels);
}
*/

void	free_map(t_map *map)
{
	int		i;

	if (!map->tiles)
		return ;
	i = 0;
	while (i < map->size.y)
	{
		free(map->tiles[i]);
		i++;
	}
	if (map->tiles)
		free(map->tiles);
	if (map->textures[NORTH].pixels)
		free(map->textures[NORTH].pixels);
	if (map->textures[SOUTH].pixels)
		free(map->textures[SOUTH].pixels);
	if (map->textures[WEST].pixels)
		free(map->textures[WEST].pixels);
	if (map->textures[EAST].pixels)
		free(map->textures[EAST].pixels);
}

void	free_program(t_program *program)
{
	free_map(program->map);
	if (program->mlx)
	{
		if (program->win)
			mlx_destroy_window(program->mlx, program->win);
		mlx_destroy_display(program->mlx);
		free(program->mlx);
	}
}
