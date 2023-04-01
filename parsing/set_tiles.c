/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:53:46 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 02:07:09 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int	set_tiles(char **lines, t_map *map)
{
	if (check_tiles(lines, map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
