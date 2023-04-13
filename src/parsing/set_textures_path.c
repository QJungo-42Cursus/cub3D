/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:52:59 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/12 13:53:28 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

typedef struct texture_path {
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}			t_texture_path;

static int	is_texture_path_valid(char *path)
{
	int			fd;

	if (ft_strnstr(path, ".xpm", ft_strlen(path) + 1) == NULL)
	{
		error_print("texture path is not valid");
		return (FALSE);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_print("texture file could not be opened");
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

static int	path_not_found(t_texture_path t, int i)
{
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

	if (set_textures_path(lines, first_line, &t) == ERROR)
		return (ERROR);
	program->map.textures[NORTH] = new_text(program->mlx, t.no_path);
	program->map.textures[SOUTH] = new_text(program->mlx, t.so_path);
	program->map.textures[EAST] = new_text(program->mlx, t.ea_path);
	program->map.textures[WEST] = new_text(program->mlx, t.we_path);
	if (program->map.textures[NORTH].pixels == NULL
		|| program->map.textures[SOUTH].pixels == NULL
		|| program->map.textures[EAST].pixels == NULL
		|| program->map.textures[WEST].pixels == NULL)
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
