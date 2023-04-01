/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:04:41 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 02:09:02 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	has_an_empty_line(char **lines)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		n = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] != ' ')
				n++;
			j++;
		}
		i++;
		if (n == 0)
			return (TRUE);
	}
	return (FALSE);
}

static int	has_only_one_spawn_point(char **lines)
{
	int		i;
	int		j;
	int		spawn_points;

	i = 0;
	spawn_points = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (is_in_charset(lines[i][j], "NSEW"))
				spawn_points++;
			j++;
		}
		i++;
	}
	if (spawn_points != 1)
		return (FALSE);
	return (TRUE);
}

static int	has_invalid_char(char **lines)
{
	int		i;
	int		j;

	i = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (!is_in_charset(lines[i][j], " 01NSEW"))
				return (TRUE);
			j++;
		}
		i++;
	}
	return (FALSE);
}

int	check_tiles(char **lines, t_map *map)
{
	(void)map;
	if (has_invalid_char(lines))
	{
		error_print("map has invalid char");
		return (ERROR);
	}
	if (has_an_empty_line(lines))
	{
		error_print("map has an empty line");
		return (ERROR);
	}
	if (!has_only_one_spawn_point(lines))
	{
		error_print("map has not only one spawn point");
		return (ERROR);
	}
	return (SUCCESS);
}
