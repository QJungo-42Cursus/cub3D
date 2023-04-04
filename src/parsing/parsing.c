/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:27:55 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 22:21:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OK 1. get tout le fichier !
// 2. separer la map du reste
// 3. verifier s'il y a des mauvais character dans la map

#include "../cube3D.h"

static int	find_map_first_line(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
	{
		if (is_in_charset(lines[i][0], " 10"))
			return (i);
		i++;
	}
	error_print("map not found");
	return (-1);
}

static int	parse_lines(char **lines, t_program *program)
{
	int		first_line;

	// TODO free all program when fail
	first_line = find_map_first_line(lines);
	if (first_line == -1)
		return (ERROR);
	if (set_colors(lines, program->map, first_line) == ERROR)
		return (ERROR);
#ifndef TEST
	if (set_textures(lines, program, first_line) == ERROR)
		return (ERROR);
#endif
	if (set_tiles(&lines[first_line], program->map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	parse(char *filename, t_program *program)
{
	char	*file_content;
	char	**lines;
	int		status;

	file_content = get_all_file(filename);
	if (file_content == NULL || ft_strlen(file_content) == 0)
		return (ERROR);
	// TODO check si la map n'est pas separee en 2 -> split efface la sep
	lines = ft_split(file_content, '\n');
	free(file_content);
	if (lines == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	status = parse_lines(lines, program);
	split_free(lines);
	return (status);
}
