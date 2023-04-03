/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:23:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/03 11:43:36 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# include "../tests/debug_helper.hpp"

# define BUFF_SIZE 2048

// TODO juste avoir un int avec du type puning ?
typedef struct s_color {
	char	r;
	char	g;
	char	b;
}	t_rgb_color;

enum e_tile {
	VOID,
	WALL,
	FLOOR,
};

enum e_direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

typedef struct s_map {
	char			*no_path;
	char			*so_path;
	char			*ea_path;
	char			*we_path;
	char			player_dir;
	char			**tiles;
	t_vec2i			player_pos;
	t_rgb_color		floor_color;
	t_rgb_color		ceiling_color;
	t_vec2i			size;
}	t_map;

//	functions

/******	./ ******/
// utils.c
void			error_print(const char *msg);
void			free_map(t_map *map);

/******	./parsing ******/
//	parsing.c
int				parse(char *filename, t_map *map);
//	get_all_file.c
char			*get_all_file(char *filename);
// get_info_by_id.c
char			*get_info_by_id(const char *id,
					char **lines, int map_first_line);
// set_textures_path.c
int				set_textures_path(char **lines, t_map *map, int first_line);
// set_colors.c
int				set_colors(char **lines, t_map *map, int first_line);
// set_tiles.c
int				set_tiles(char **lines, t_map *map);
// check_tiles.c
int				check_tiles(char **lines, t_map *map);
// check_tiles_after.c
int				check_tiles_after(t_map *map);

#endif /* CUBE3D_H */
