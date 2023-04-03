/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:23:27 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 00:26:31 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void	add_to_result(char **result, char *to_add)
{
	char	*tmp;

	if (to_add == NULL || ft_strlen(to_add) == 0)
		return ;
	if (*result == NULL)
	{
		*result = ft_strdup(to_add);
		return ;
	}
	tmp = *result;
	*result = ft_strjoin(*result, to_add);
	free(tmp);
	if (*result == NULL)
	{
		error_print("malloc error");
		exit(1);
	}
	return ;
}

char	*get_all_file(char *filename)
{
	int		fd;
	char	buf[BUFF_SIZE];
	char	*result;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error_print("could not open file");
		return (NULL);
	}
	result = NULL;
	while (1)
	{
		count = read(fd, buf, BUFF_SIZE - 1);
		buf[count] = '\0';
		add_to_result(&result, buf);
		if (count == 0)
			break ;
	}
	if (result == NULL || ft_strlen(result) == 0)
		error_print("file is empty");
	return (result);
}
