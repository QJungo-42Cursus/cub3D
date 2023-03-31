/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:16:25 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 01:22:11 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

void	error_print(char *msg)
{
	static int	first = TRUE;

	if (!first)
		return ;
	first = FALSE;
	ft_printf("Error\n%s\n", msg);
}
