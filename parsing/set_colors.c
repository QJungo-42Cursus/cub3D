/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:28:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 01:48:06 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	set_into_color(char *color, t_rgb_color *rgb_color)
{
	char		**split;

	split = ft_split(color, ',');
	if (split == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	if (split[0] == NULL
		|| split[1] == NULL || split[2] == NULL || split[3] != NULL)
	{
		error_print("color format error");
		split_free(split);
		return (ERROR);
	}
	rgb_color->r = ft_atoi(split[0]);
	rgb_color->g = ft_atoi(split[1]);
	rgb_color->b = ft_atoi(split[2]);
	split_free(split);
	return (SUCCESS);
}

int	set_colors(char **lines, t_map *map, int first_line)
{
	char	*floor_color;
	char	*ceiling_color;
	int		result;

	floor_color = get_info_by_id("F ", lines, first_line);
	if (floor_color == NULL)
	{
		error_print("floor color not found");
		return (ERROR);
	}
	ceiling_color = get_info_by_id("C ", lines, first_line);
	if (ceiling_color == NULL)
	{
		error_print("ceiling color not found");
		free(floor_color);
		return (ERROR);
	}
	result = SUCCESS;
	if (set_into_color(floor_color, &map->floor_color) == ERROR)
		result = ERROR;
	if (set_into_color(ceiling_color, &map->ceiling_color) == ERROR)
		result = ERROR;
	free(floor_color);
	free(ceiling_color);
	return (result);
}
