/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:22:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 18:17:33 by qjungo           ###   ########.fr       */
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

int close_window()
{
	exit(0);
	return 0;
}

int key_hook()
{
	return 0;
}

void	main_loop(t_program *program)
{

	mlx_hook(program->win, ON_DESTROY, 0, close_window, NULL);
	mlx_hook(program->win, ON_KEYDOWN, 0, key_hook, NULL);
	mlx_loop(program->mlx);
}

int	main_(int argc, char **argv)
{
	t_map		map;
	t_program	program;

	program.map = &map;

	init_program(&program);
	if (!is_arg_name_valid(argc, argv))
	{
		error_print("usage: ./cub3D [map_file].cub");
		free_program(&program);
		return (1);
	}
	if (parse(argv[1], &program) == ERROR)
		return (1);
	main_loop(&program);
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
