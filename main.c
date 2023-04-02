/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:22:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/02 18:46:56 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/debug_helper.hpp"
#include "cube3D.h"

static int	is_arg_name_valid(int argc, char **argv)
{
	int		len;

	if (argc != 2)
		return (FALSE);
	len = ft_strlen(argv[1]);
	if (len < 5)
		return (FALSE);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 5) != 0)
		return (FALSE);
	return (TRUE);
}

static void	init_map(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->tiles = NULL;
	map->size.x = 0;
	map->size.y = 0;
	map->ceiling_color.r = 0;
	map->ceiling_color.g = 0;
	map->ceiling_color.b = 0;
	map->floor_color.r = 0;
	map->floor_color.g = 0;
	map->floor_color.b = 0;
	map->player_pos.x = 0;
	map->player_pos.y = 0;
	map->player_dir = 0;
}

int	main_(int argc, char **argv)
{
	t_map	map;

	init_map(&map);
	if (!is_arg_name_valid(argc, argv))
	{
		error_print("usage: ./cub3D [map_file].cub");
		return (1);
	}
	if (parse(argv[1], &map) == ERROR)
		return (1);
	free_map(&map);
	return (0);
}
//LOG_TILES(map);

#ifndef TEST

int	main(int argc, char **argv)
{
	main_(argc, argv);
}

#endif
