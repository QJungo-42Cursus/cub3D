#ifndef CUBE3D_H
# define CUBE3D_H
# include "libft/libft.h"

// TODO juste avoir un int avec du type puning ?
typedef struct s_color {
	char	r;
	char	g;
	char	b;
}	t_rgb_color;

typedef enum e_tile {
	VOID,	// <space>
	WALL,	// <1>
	FLOOR,	// <0>
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

//	parsing/
//	parsing.c
void	parse(char *filename);

#endif /* CUBE3D_H */
