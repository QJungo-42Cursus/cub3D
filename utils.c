/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 02:30:00 by qjungo           ###   ########.fr       */
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

void	free_map(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->tiles)
		split_free(map->tiles);
}
