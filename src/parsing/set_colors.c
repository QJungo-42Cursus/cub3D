/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:28:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 17:55:53 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	set_into_color(char *color_str, unsigned int *rgb)
{
	char		**split;

	split = ft_split(color_str, ',');
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
	*rgb = color_from_rgb(ft_atoi(split[0]),
			ft_atoi(split[1]),
			ft_atoi(split[2]));
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
		return (ERROR);
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
