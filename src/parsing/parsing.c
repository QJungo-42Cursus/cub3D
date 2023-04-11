/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:27:55 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/11 14:31:18 by qjungo           ###   ########.fr       */
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

	first_line = find_map_first_line(lines);
	if (first_line == -1)
		return (ERROR);
	if (set_colors(lines, &program->map, first_line) == ERROR)
		return (ERROR);
	if (set_textures(lines, program, first_line) == ERROR)
		return (ERROR);
	if (set_tiles(&lines[first_line], program) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	open_goto_map_start(char *filename, char **line, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (ERROR);
	while (1)
	{
		*line = get_next_line(*fd);
		if (*line == NULL)
			break ;
		if (is_in_charset((*line)[0], " 01"))
		{
			free(*line);
			break ;
		}
		free(*line);
	}
	return (SUCCESS);
}

static int	is_map_compact(char *filename)
{
	char	*line;
	int		has_empty_line;
	int		fd;

	if (open_goto_map_start(filename, &line, &fd) == ERROR)
		return (FALSE);
	has_empty_line = FALSE;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (has_empty_line && line[0] != '\n' && line[1] != '\0')
		{
			free(line);
			return (FALSE);
		}
		if (line[0] == '\n')
			has_empty_line = TRUE;
		free(line);
	}
	return (TRUE);
}

int	parse(char *filename, t_program *program)
{
	char	*file_content;
	char	**lines;
	int		status;

	file_content = get_all_file(filename);
	if (file_content == NULL || ft_strlen(file_content) == 0)
		return (ERROR);
	if (!is_map_compact(filename))
	{
		free(file_content);
		error_print("map has an empty line");
		return (ERROR);
	}
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
