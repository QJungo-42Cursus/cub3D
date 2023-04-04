

#include "../../src/cube3D.h"
#define C_RED 0xffFF0000
#define C_GREEN 0xff00FF00
#define C_BLUE 0xff0000FF
#define C_WHITE 0xffFFFFFF
#define C_BLACK 0xff000000

void	draw_rect(t_img_data *img_data, t_vec2i pos, t_vec2i size, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (pos.x + j < 0 || pos.x + j >= img_data->size.x || pos.y + i < 0 || pos.y + i >= img_data->size.y)
				return ;
			pixel_to_image(img_data, new_vec2(pos.x + j, pos.y + i), color);
			j++;
		}
		i++;
	}
}

void	minimap_draw(t_img_data *img_data, t_map *map)
{
	int		i;
	int		j;
	t_vec2i	pos;
	t_vec2i	size;
	t_color	color;

	size = (t_vec2i){ 10, 10 };
	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			pos = (t_vec2i){ j * size.x, i * size.y };
			if (map->tiles[i][j] == '1')
				color = C_BLACK;
			else
				color = C_RED;
			draw_rect(img_data, pos, size, color);
			j++;
		}
		i++;
	}
}
#include <math.h>
void	draw_raycast(t_vec2 player_pos, t_map *map, t_img_data *img_data, int fov)
{
	int x_pos = 0;
	double ray_pos;

	ray_pos = -(fov / 2.);
	while (x_pos < img_data->size.x)
	{
		// y = ax + b
		double a = tan(deg_to_rad(ray_pos)); // y / x
		printf("ray_pos: %f, a: %f\n", ray_pos, a);
		t_vec2 dir = new_vec2(1, a);
		double x;
		double y;
		/*
		for (int i = 0; i < 1000; i++)
		{
			x += 0.1;
			y = a * x + b;
			//printf("x: %d, y: %d\n", (int)x, (int)y);
		}
		*/

		int k = 100;
		x = 100 + player_pos.x;
		y = a * x + player_pos.y;
		//x = player_pos.x + k * dir.x;
		//y = player_pos.y + k * dir.y;
		t_vec2	p1 = new_vec2(player_pos.x, player_pos.y);
		t_vec2	p2 = new_vec2(x + player_pos.x, y + player_pos.y);
		//printf("p1: %d, %d, p2: %d, %d\n", (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);

		if (x < 0 || x >= img_data->size.x || y < 0 || y >= img_data->size.y)
		{
			printf("x: %d, y: %d\n", (int)x, (int)y);
		}
		else
		{
			draw_line(new_line(p1, p2, C_WHITE), img_data);
		}
		ray_pos = x_pos / (double)img_data->size.x * fov - fov / 2.;
		x_pos += 1;
	}
}


int main()
{
	t_vec2i		size =		{ 2 * 720, 2 * 480 };
	void		*mlx =		mlx_init();
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_img_data	img_data =	new_img_data(mlx, size);
	t_map		map =		{ .size = (t_vec2i){ 10, 10 } };
	t_vec2		player_pos = new_vec2(100, 100);

	map.tiles = malloc(sizeof(char *) * map.size.y);
	map.tiles[0] = "1111111111";
	map.tiles[1] = "1000000001";
	map.tiles[2] = "1000000001";
	map.tiles[3] = "1000000001";
	map.tiles[4] = "1000000001";
	map.tiles[5] = "1000000001";
	map.tiles[6] = "1011110001";
	map.tiles[7] = "1001000001";
	map.tiles[8] = "1000000001";
	map.tiles[9] = "1111111111";

	fillscreen(&img_data, C_BLUE, C_BLUE);

	//minimap_draw(&img_data, &map);
	//draw_rect(&img_data, new_vec2i(player_pos.x, player_pos.y), new_vec2i(10, 10), C_GREEN);
	draw_raycast(player_pos, &map, &img_data, 90);
	player_pos = new_vec2(130, 100);
	//draw_raycast(player_pos, &map, &img_data, 20);
	//draw_line(new_line(new_vec2(0, 0), new_vec2(100, 100), C_WHITE), &img_data);

	mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);
	//mlx_key_hook(win, key_hook, ptr);
	//mlx_loop_hook(mlx, loop_hook, ptr);
	mlx_loop(mlx);
}
