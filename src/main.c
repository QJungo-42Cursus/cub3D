/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:22:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 12:18:56 by qjungo           ###   ########.fr       */
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

int	main_(int argc, char **argv)
{
	t_program	program;

	init_program(&program);
	if (!is_arg_name_valid(argc, argv))
	{
		error_print("usage: ./cub3D [map_file].cub");
		free_program(&program);
		return (1);
	}
	if (parse(argv[1], &program) == ERROR)
	{
		free_program(&program);
		return (1);
	}
	if (init_win(&program) == ERROR)
	{
		free_program(&program);
		return (1);
	}
	run(&program);
	free_program(&program);
	return (0);
}

#ifndef TEST

int	main(int argc, char **argv)
{
	main_(argc, argv);
}

#endif
