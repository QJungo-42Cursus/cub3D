/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:53:46 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 04:44:02 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void	set_map_size(char **lines, t_map *map)
{
	int		largest_x;
	int		i;

	map->size.y = 0;
	while (lines[map->size.y] != NULL)
		map->size.y++;
	largest_x = 0;
	i = 0;
	while (lines[i] != NULL)
	{
		if (ft_strlen(lines[i]) > largest_x)
			largest_x = ft_strlen(lines[i]);
		i++;
	}
	map->size.x = largest_x;
}

static void	allocate_tiles(t_map *map)
{
	int		i;

	map->tiles = (char **)malloc(sizeof(char *) * map->size.y);
	if (map->tiles == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	i = 0;
	while (i < map->size.y)
	{
		map->tiles[i] = (char *)ft_calloc(map->size.x, sizeof(char));
		if (map->tiles[i] == NULL)
		{
			error_print("malloc error");
			exit(1);
		}
		i++;
	}
}

static int	set_player_spawn(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_pos.x = x;
		map->player_pos.y = y;
		map->player_dir = c;
		return (SUCCESS);
	}
	return (ERROR);
}

static int	file_tiles(char **lines, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == ' ')
				map->tiles[i][j] = VOID;
			else if (lines[i][j] == '0')
				map->tiles[i][j] = FLOOR;
			else if (lines[i][j] == '1')
				map->tiles[i][j] = WALL;
			else
			{
				map->tiles[i][j] = FLOOR;
				set_player_spawn(lines[i][j], map, j, i);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	set_tiles(char **lines, t_map *map)
{
	if (check_tiles(lines, map) == ERROR)
		return (ERROR);
	set_map_size(lines, map);
	if (map->size.x == 0 || map->size.y == 0)
		return (ERROR);
	allocate_tiles(map);
	file_tiles(lines, map);
	if (check_tiles_after(map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
