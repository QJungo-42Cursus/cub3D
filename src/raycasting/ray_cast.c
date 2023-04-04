/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:13 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/04 16:20:25 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

typedef struct s_player {
	t_vec2	pos;
	t_vec2	dir_cam;
	t_vec2	cam_plan;
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

static int	is_a_wall(t_vec2i coor, char **tiles)
{
	return (tiles[coor.y][coor.x] == '1');
}

void	set_player(t_player *player)
{
	player->pos.x = 0.5;
	player->pos.y = 0.5;
	player->dir_cam.x = 1;
	player->dir_cam.y = 0;
	player->cam_plan.x = 0;
	player->cam_plan.y = 0.66;
}

// TODO
// - le faire sans les steps (avec round ?)
void	get_impact(t_player *player, t_ray *ray, t_map *map, int s_x, t_img_data *img)
{
	int		hit;
	int		side;

	ray->pos_tile.x = (int)player->pos.x;
	ray->pos_tile.y = (int)player->pos.y;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos_tile.x += ray->step.x;
			side = 0;
		}
		else
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos_tile.y += ray->step.y;
			side = 1;
		}
		if (is_a_wall(ray->pos_tile, map->tiles))
			hit = 1;
	}
	if (side == 0)
		ray->perpWalldist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perpWalldist = (ray->side_dist.y - ray->delta_dist.y);

	int h = 500;
	int lineHeight = (int)(h / ray->perpWalldist);
	static t_vec2i last_impact = {0, 0};

	t_color_gradient lll;
	if (last_impact.x != ray->pos_tile.x || last_impact.y != ray->pos_tile.y)
	{
		printf("impact: %d, %d\n", ray->pos_tile.x, ray->pos_tile.y);
		last_impact.x = ray->pos_tile.x;
		last_impact.y = ray->pos_tile.y;
	}
}

void	init_ray(t_player *player, t_ray *ray)
{
	ray->pos_tile.x = (int)player->pos.x;
	ray->pos_tile.y = (int)player->pos.y;
}

void	set_ray(t_player *play, t_ray *ray, t_vec2 cam, int x)
{
	ray->dir.x = play->dir_cam.x + play->cam_plan.x * cam.x;
	ray->dir.y = play->dir_cam.y + play->cam_plan.y * cam.x;
	ray->delta_dist.x
		= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->delta_dist.y
		= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	new_vec2(&ray->step, 1, 1);
	ray->side_dist.x = (ray->pos_tile.x + 1 - play->pos.x) * ray->delta_dist.x;
	ray->side_dist.y = (ray->pos_tile.y + 1 - play->pos.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (play->pos.x - ray->pos_tile.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (play->pos.y - ray->pos_tile.y) * ray->delta_dist.y;
	}
	ray->perpWalldist = 0;
}

void	ray_casting_loop(t_player *player, t_map *map, t_img_data *img)
{
	int		x;
	t_ray	ray;
	t_vec2	cam;

	x = 0;
	init_ray(player, &ray);
	while (x < img->size.x)
	{
		cam.x = 2 * x / (double) img->size.x + 1;
		set_ray(player, &ray, cam, x);
		get_impact(player, &ray, map, x, img);
		x++;
	}
}

int main()
{
	void		*mlx =		mlx_init();
	t_vec2i		size =		{ 1920 / 2, 1080 / 2 };
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_img_data	img_data =	new_img_data(mlx, size);
	t_player	player;

	set_player(&player);

	t_map map;
	map.size.x = 6;
	map.size.y = 9;
	map.tiles = malloc(8 * 80);
	map.tiles[0] = ft_strdup("111111");
	map.tiles[1] = ft_strdup("110101");
	map.tiles[2] = ft_strdup("100100");
	map.tiles[3] = ft_strdup("100000");
	map.tiles[4] = ft_strdup("100000");
	map.tiles[5] = ft_strdup("100000");
	map.tiles[6] = ft_strdup("100100");
	map.tiles[7] = ft_strdup("100000");
	map.tiles[8] = ft_strdup("111111");

	while (1) {
		//player.pos.x += 0.1;
		player.dir_cam.x += 0.01;
		ray_casting_loop(&player, &map, &img_data);
		mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);
	}
	return (0);
}
