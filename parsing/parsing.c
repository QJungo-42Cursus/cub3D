// OK 1. get tout le fichier !
// 2. separer la map du reste
// 3. verifier s'il y a des mauvais character dans la map

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "../libft/libft.h"

#define BUFF_SIZE 2048

static int	add_to_result(char **result, char *to_add)
{
	char	*tmp;

	if (to_add == NULL || ft_strlen(to_add) == 0)
		return (SUCCESS); // TODO sur ?
	if (*result == NULL)
	{
		*result = ft_strdup(to_add);
		return (SUCCESS);
	}
	tmp = *result;
	*result = ft_strjoin(*result, to_add);
	free(tmp);
	if (*result == NULL)
		return (ERROR);
	return (SUCCESS);
}

static char	*get_all_file(char *filename)
{
	int		fd;
	char	buf[BUFF_SIZE];
	char	*result;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);

	result = NULL;
	while (1)
	{
		count = read(fd, buf, BUFF_SIZE - 1);
		buf[count] = '\0';
		if (add_to_result(&result, buf) == ERROR)
			return (NULL);
		if (count == 0)
			break ;
	}
	return (result);
}

void	parse(char *filename)
{
	char	*file_content;

	file_content = get_all_file(filename);
	ft_printf("%s", file_content);
	free(file_content);
}
