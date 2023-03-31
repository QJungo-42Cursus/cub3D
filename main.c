/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:22:39 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 00:22:41 by qjungo           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map	map;

	if (!is_arg_name_valid(argc, argv))
	{
		error_print("usage: ./cub3D [map_file].cub");
		return (1);
	}
	if (parse(argv[1], &map) == ERROR)
		return (1);
	return (0);
}
