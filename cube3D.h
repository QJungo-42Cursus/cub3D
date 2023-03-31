/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:23:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/01 00:52:38 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFF_SIZE 2048

// TODO juste avoir un int avec du type puning ?
typedef struct s_color {
	char	r;
	char	g;
	char	b;
}	t_rgb_color;

typedef enum e_tile {
	VOID,
	WALL,
	FLOOR,
}	t_tile;

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

//	functions

/******	./ ******/
// utils.c
void			error_print(char *msg);

/******	./parsing ******/
//	parsing.c
int				parse(char *filename, t_map *map);
//	get_all_file.c
char			*get_all_file(char *filename);
// get_info_by_id.c
char			*get_info_by_id(char *id, char **lines, int map_first_line);
// set_textures_path
int				set_textures_path(char **lines, t_map *map, int first_line);

#endif /* CUBE3D_H */
