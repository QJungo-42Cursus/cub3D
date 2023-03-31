/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:27:55 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 00:53:56 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OK 1. get tout le fichier !
// 2. separer la map du reste
// 3. verifier s'il y a des mauvais character dans la map

#include "../libft/libft.h"
#include "../cube3D.h"

int	find_map_first_line(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
	{
		if (is_in_charset(lines[i][0], " 10"))
			return (i);
		i++;
	}
	return (-1);
}


int	parse_lines(char **lines, t_map *map)
{
	int		first_line;

	first_line = find_map_first_line(lines);
	if (set_textures_path(lines, map, first_line) == ERROR)
		return (ERROR);
	// TODO
	return (SUCCESS);
}

int	parse(char *filename, t_map *map)
{
	char	*file_content;
	char	**lines;

	file_content = get_all_file(filename);
	if (file_content == NULL || ft_strlen(file_content) == 0)
		return (ERROR);
	// TODO check si la map n'est pas separee en 2 block
	// -> le split va effacer la separation entre les 2 (donc on ne vera pas l'erreur)
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (lines == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	return (parse_lines(lines, map));
}

/*
typedef struct s_map {
	char			*no_path;
	char			*so_path;
	char			*ea_path;
	char			*we_path;
	t_rgb_color		floor_color;
	t_rgb_color		ceiling_color;
	t_tile			**tiles;
	t_vec2			size;
}	t_map;
*/
