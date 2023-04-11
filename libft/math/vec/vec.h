/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:53:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 22:28:37 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_vec2 {
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec2i {
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec3 {
	float	x;
	float	y;
	float	z;
}	t_vec3;

//			new
t_vec2		new_vec2(float x, float y);
t_vec2i		new_vec2i(int x, int y);
t_vec3		new_vec3(float x, float y, float z);

//			conversion
t_vec2		vec3_to2(t_vec3 v);
t_vec3		vec2_to3(t_vec2 v);
t_vec2		angle_to_vec2(double angle);
double		vec2_to_angle(t_vec2 v);

//			copy
t_vec3		*copy_vec3_list(t_vec3 *src, int size);
t_vec2		*copy_vec2_list(t_vec2 *src, int size);
void		copy_vec3_list_to2(t_vec3 *src, int size, t_vec2 *dst);

// assert
int			assert_rounded_vec2(t_vec2 a, t_vec2 b);
int			assert_vec2i(t_vec2i a, t_vec2i b);

double		vec2_dist(t_vec2 a, t_vec2 b);

#endif /* VEC_H */
