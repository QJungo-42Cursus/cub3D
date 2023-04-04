/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:23:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/04/04 17:54:57 by qjungo           ###   ########.fr       */
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

# define C_RED		(t_rgb)0xffFF0000
# define C_GREEN	(t_rgb)0xff00FF00
# define C_BLUE		(t_rgb)0xff0000FF
# define C_WHITE	(t_rgb)0xffFFFFFF
# define C_BLACK	(t_rgb)0xff000000

# include "../tests/debug_helper.hpp"

# define BUFF_SIZE 2048

enum e_tile {
	VOID = ' ',
	FLOOR = '0',
	WALL = '1',
};

typedef enum e_direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_direction;

typedef struct s_map {
	t_texture		textures[4];
	char			**tiles;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	t_vec2i			size;
}	t_map;

typedef struct s_player {
	t_direction		dir; // spawn dir
	t_vec2			pos;
	t_vec2			dir_cam;
	t_vec2			cam_plan;
}	t_player;

typedef struct s_ray {
	t_vec2i	pos_tile;
	t_vec2	dir;
	t_vec2	delta_dir;
	t_vec2	delta_dist;
	t_vec2	side_dist;
	t_vec2	step;
	double	perpWalldist;
}	t_ray;

typedef struct s_program {
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	t_bool		refresh;
	t_img_data	img_data;
}	t_program;

//	functions

/******	./ ******/
// utils.c
void			error_print(const char *msg);
void			free_program(t_program *program);
int				init_win(t_program *program);
void			init_program(t_program *program);

// player_action.c
t_vec2	vec2_from_angle(double angle);
void	set_player_cam(t_player *player, char c);
void	rotate_cam(t_player *player, double angle);
void	set_player_cam(t_player *player, char c);

/******	./raycast ******/
// ray_cast.c
void			ray_casting_loop(t_program *prog, t_img_data *img_data);
void			set_ray(t_player play, t_ray *ray, t_vec2 cam);
void			get_impact(t_ray *ray, t_map *map);

/******	./run ******/
// run.c
void			run(t_program *program);
// draw_minimap.c
void			draw_minimap(t_program *program,
					t_img_data *img_data, t_vec2i start, t_vec2 size);
// move_toward.c
void			move_toward(t_player *player, t_map map, t_vec2i dir);

/******	./parsing ******/
//	parsing.c
int				parse(char *filename, t_program *program);
//	get_all_file.c
char			*get_all_file(char *filename);
// get_info_by_id.c
char			*get_info_by_id(const char *id,
					char **lines, int map_first_line);
// set_textures_path.c
int				set_textures(char **lines, t_program *program, int first_line);
// set_colors.c
int				set_colors(char **lines, t_map *map, int first_line);
// set_tiles.c
int				set_tiles(char **lines, t_program *program);
// check_tiles.c
int				check_tiles(char **lines, t_map *map);
// check_tiles_after.c
int				check_tiles_after(t_map *map);



/******** ./fillscreen ******/
// fillscreen.c
void	fillscreen(t_img_data *img_data, t_rgb ceiling_color, t_rgb floor_color);

#endif /* CUBE3D_H */
