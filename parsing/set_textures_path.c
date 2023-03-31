/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:52:59 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 01:38:53 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	is_texture_path_valid(char *path)
{
	static int	one_invalid = FALSE;

	if (one_invalid)
		return (FALSE);
	if (ft_strnstr(path, ".xpm", ft_strlen(path) + 1) == NULL)
	{
		one_invalid = TRUE;
		error_print("texture path is not valid");
		return (FALSE);
	}
	return (TRUE);
}

static int	path_not_found(t_map *map, int i)
{
	if (i < 4)
		error_print("path not found");
	free(map->no_path);
	if (i > 1)
		free(map->so_path);
	if (i > 2)
		free(map->we_path);
	if (i > 3)
		free(map->ea_path);
	return (ERROR);
}

int	set_textures_path(char **lines, t_map *map, int first_line)
{
	map->no_path = get_info_by_id("NO ", lines, first_line);
	if (map->no_path == NULL)
		return (path_not_found(map, 0));
	map->so_path = get_info_by_id("SO ", lines, first_line);
	if (map->so_path == NULL)
		return (path_not_found(map, 1));
	map->we_path = get_info_by_id("WE ", lines, first_line);
	if (map->we_path == NULL)
		return (path_not_found(map, 2));
	map->ea_path = get_info_by_id("EA ", lines, first_line);
	if (map->ea_path == NULL)
		return (path_not_found(map, 3));
	if (!is_texture_path_valid(map->ea_path)
		|| !is_texture_path_valid(map->so_path)
		|| !is_texture_path_valid(map->we_path)
		|| !is_texture_path_valid(map->no_path))
		return (path_not_found(map, 4));
	return (SUCCESS);
}
