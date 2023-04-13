/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_by_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:50:34 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 17:55:42 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static char	*return_value(const char *id, char **lines, int found_i)
{
	char	*value;

	if (found_i == -1)
		return (NULL);
	value = ft_strdup(&lines[found_i][ft_strlen(id)]);
	if (value == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	return (value);
}

char	*get_info_by_id(const char *id, char **lines, int map_first_line)
{
	int		i;
	int		found_i;

	i = 0;
	found_i = -1;
	while (lines[i] != NULL)
	{
		if (ft_strncmp(lines[i], id, ft_strlen(id)) == 0)
		{
			if (found_i != -1)
				error_print("multiple definition for same texture or color");
			else if (i > map_first_line)
				error_print("map is not at the end of the file");
			if (i > map_first_line || found_i != -1)
				return (NULL);
			found_i = i;
		}
		i++;
	}
	if (found_i == -1)
		error_print("texture path or color not found");
	return (return_value(id, lines, found_i));
}
