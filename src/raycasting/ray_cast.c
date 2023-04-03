/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/03 19:25:52 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

typedef struct s_player {
	t_vec2	pos;
	t_vec2	dir_cam;
	t_vec2	cam_plan;
}	t_player;

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	if (tiles[coor.y][coor.x] == '1')
		return (1);
	else
		return (0);
}

void	set_player(t_player *player)
{
	player->pos.x = 3;
	player->pos.y = 3;
	player->dir_cam.x = -1;
	player->dir_cam.y = 0;
	player->cam_plan.x = 0;
	player->cam_plan.y = 0.66;
}

// TODO
// - le faire sans les steps (avec round ?)
void	get_impact(t_player *player, t_vec2 *ray_dir, t_vec2 *delta_dist, t_map *map, int s_x, t_img_data *img)
{
	t_vec2i	map_c;
	t_vec2	side_dist;
	t_vec2	step;
	double	perpWalldist;
	int		hit;
	int		side;

	map_c.x = (int)player->pos.x;
	map_c.y = (int)player->pos.y;
	if (ray_dir->x < 0)
	{
		step.x = -1;
		side_dist.x = (player->pos.x - map_c.x) * delta_dist->x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map_c.x + 1 - player->pos.x) * delta_dist->x;
	}
	if (ray_dir->y < 0)
	{
		step.y = -1;
		side_dist.y = (player->pos.y - map_c.y) * delta_dist->y;
	}
	else
	{
		step.y = 1;
		side_dist.x = (map_c.y + 1 - player->pos.y) * delta_dist->y;
	}
	while (hit == 0)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist->x;
			map_c.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.x += delta_dist->x;
			map_c.y += step.y;
			side = 1;
		}
		if (is_a_wall(map_c, map->tiles))
			hit = 1;
	}
	if (side == 0)
		perpWalldist = (side_dist.x - delta_dist->x);
	else
		perpWalldist = (side_dist.y - delta_dist->y);
	int h = 1;
	int lineHeight = (int)(h / perpWalldist);

	t_color_gradient lll;
	lll.start = 0xff22ff22;
	t_line line = new_line(new_vec2(s_x, img->size.y / 2 - lineHeight / 2), new_vec2(s_x, img->size.y / 2 + lineHeight / 2), lll, 1);
	draw_line(img, line);

}

void	ray_casting_loop(t_player *player, t_map *map, t_img_data *img)
{
	int		x;
	t_vec2	ray_dir;
	t_vec2	delta_dir;
	t_vec2	cam;

	x = 0;
	while (x < map->size.x)
	{
		cam.x = 2 * x / (double) map->size.x + 1;
		ray_dir.x = player->dir_cam.x + player->cam_plan.x * cam.x;
		ray_dir.y = player->dir_cam.y + player->cam_plan.y * cam.x;
		delta_dir.x
			= sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
		delta_dir.y
			= sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		get_impact(player, &ray_dir, &delta_dir, map, x, img);
		x++;
	}
}

int main()
{
	void		*mlx =		mlx_init();
	t_vec2i		size =		{ 1920, 1080 };
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_img_data	img_data =	new_img_data(mlx, size);
	t_player	player;

	set_player(&player);

	t_map map;
	map.tiles = malloc(8 * 80);
	map.tiles[0] = ft_strdup("111111");
	map.tiles[1] = ft_strdup("100001");
	map.tiles[2] = ft_strdup("100001");
	map.tiles[3] = ft_strdup("100001");
	map.tiles[4] = ft_strdup("100001");
	map.tiles[5] = ft_strdup("111111");

	ray_casting_loop(&player, &map, &img_data);

	mlx_put_image_to_window(mlx, win, &img_data, 0, 0);
	mlx_loop(mlx);
	return (0);
}
