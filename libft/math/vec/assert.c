/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:35:34 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/02 10:36:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

int	assert_rounded_vec2(t_vec2 a, t_vec2 b)
{
	return ((round(a.x) == round(b.x)) && (round(a.y) == round(b.y)));
}

int	assert_vec2i(t_vec2i a, t_vec2i b)
{
	return (a.x == b.x && a.y == b.y);
}
