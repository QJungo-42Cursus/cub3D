/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:52:59 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 16:10:02 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

typedef struct texture_path {
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}			t_texture_path;

static int	is_texture_path_valid(char *path)
{
	static int	one_invalid = FALSE;
	int			fd;

	if (one_invalid)
		return (FALSE);
	if (ft_strnstr(path, ".xpm", ft_strlen(path) + 1) == NULL)
	{
		one_invalid = TRUE;
		error_print("texture path is not valid");
		return (FALSE);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		one_invalid = TRUE;
		error_print("texture path is not valid");
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

static int	path_not_found(t_texture_path t, int i)
{
	if (i < 4)
		error_print("path not found");
	free(t.no_path);
	if (i > 1)
		free(t.so_path);
	if (i > 2)
		free(t.we_path);
	if (i > 3)
		free(t.ea_path);
	return (ERROR);
}

static int	set_textures_path(char **lines, int first_line, t_texture_path *t)
{
	t->no_path = get_info_by_id("NO ", lines, first_line);
	if (t->no_path == NULL)
		return (path_not_found(*t, 0));
	t->so_path = get_info_by_id("SO ", lines, first_line);
	if (t->so_path == NULL)
		return (path_not_found(*t, 1));
	t->we_path = get_info_by_id("WE ", lines, first_line);
	if (t->we_path == NULL)
		return (path_not_found(*t, 2));
	t->ea_path = get_info_by_id("EA ", lines, first_line);
	if (t->ea_path == NULL)
		return (path_not_found(*t, 3));
	if (!is_texture_path_valid(t->ea_path)
		|| !is_texture_path_valid(t->so_path)
		|| !is_texture_path_valid(t->we_path)
		|| !is_texture_path_valid(t->no_path))
		return (path_not_found(*t, 4));
	return (SUCCESS);
}

int	set_textures(char **lines, t_program *program, int first_line)
{
	t_texture_path	t;

	set_textures_path(lines, first_line, &t);

	program->map->textures[NORTH] = new_text(program->mlx, t.no_path);
	if (program->map->textures[NORTH].pixels == NULL)
	{
		error_print("malloc error");
		return (ERROR);
	}
	program->map->textures[SOUTH] = new_text(program->mlx, t.so_path);
	if (program->map->textures[SOUTH].pixels == NULL)
	{
		error_print("malloc error");
		return (ERROR);
	}
	program->map->textures[WEST] = new_text(program->mlx, t.we_path);
	if (program->map->textures[WEST].pixels == NULL)
	{
		error_print("malloc error");
		return (ERROR);
	}
	program->map->textures[EAST] = new_text(program->mlx, t.ea_path);
	if (program->map->textures[EAST].pixels == NULL)
	{
		error_print("malloc error");
		return (ERROR);
	}
	free(t.no_path);
	free(t.so_path);
	free(t.we_path);
	free(t.ea_path);
	return (SUCCESS);
}
