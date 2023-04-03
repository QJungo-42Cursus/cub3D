/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:22:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 16:08:21 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	init_mlx(t_program *program)
{
	program->mlx = mlx_init();
	if (program->mlx == NULL)
	{
		error_print("mlx_init error");
		return (FALSE);
	}
	// TODO set size
	program->win = mlx_new_window(program->mlx, 1600, 900, (char *)"cube3D");
	if (program->win == NULL)
	{
		error_print("mlx_new_window error");
		mlx_destroy_display(program->mlx);
		free(program->mlx);
		return (FALSE);
	}
	return (SUCCESS);
}

int	main_(int argc, char **argv)
{
	t_map		map;
	t_program	program;

	program.map = &map;

	init_map(&map);
	init_mlx(&program);
	if (!is_arg_name_valid(argc, argv))
	{
		error_print("usage: ./cub3D [map_file].cub");
		free_program(&program);
		return (1);
	}
	if (parse(argv[1], &program) == ERROR)
		return (1);
	free_program(&program);
	return (0);
}
//LOG_TILES(map);

#ifndef TEST

int	main(int argc, char **argv)
{
	main_(argc, argv);
}

#endif
