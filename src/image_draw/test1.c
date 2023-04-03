#include "../cube3D.h"
#include <math.h>
/// texture column to image
void	text_column_to_img(
			t_texture texture,
			t_img_data img_data,
			int img_x,
			int text_x,
			float scale,
			float shift
)
{
	t_vec2i		img_index;
	t_vec2		text_index;

	text_index.x = text_x;
	img_index.x = img_x;
	img_index.y = 0;
	text_index.y = 0;
	while (img_index.y < (texture.size.y - 1) * scale) // le -1 pour eviter les vieux pixels multi color en bas...
	{
		*(pixel_addr(img_index.x, img_index.y + shift, &img_data)) = texture.pixels[(int)roundf(text_index.x) + (int)roundf(text_index.y) * texture.size.y];
		img_index.y++;
		text_index.y += 1.f / scale;
	}
}

void	texture_to_image_with_shift(t_texture texture, void *mlx, void *img, float scale, t_vec2i img_size, t_vec2 position)
{
	t_vec2		img_index;
	t_vec2		text_index;
	t_img_data	img_data;

	img_index.x = position.x;
	float shift = position.y;
	img_data = img_data_from(img);


	text_index.x = 0;
	float y_scale = scale * 0.5;
	while (img_index.x < texture.size.x * scale)
	{
		text_column_to_img(texture, img_data, img_index.x, text_index.x, y_scale, shift);
		img_index.x += 1.f;
		text_index.x += 1.f / scale;
		y_scale += 0.005;
		shift -= 0.1;
		if (shift < 0)
			shift = 0;
	}
}

void	test1()
{
	void	*mlx;
	void	*win;
	t_vec2i	size = { 1920, 1080 };

	mlx = mlx_init();
	win = mlx_new_window(mlx, size.x, size.y, "cc");

	t_texture texture = new_text(mlx, "../textures/wood.xpm");
	void	*img = mlx_new_image(mlx, size.x, size.y);
	void	*blank_img = mlx_new_image(mlx, size.x, size.y);

	float scale = 8;
	float add = 0.1;
	t_vec2 position = { 100, 100 };
	t_vec2 position2 = { 0, 0 };
	texture_to_image_with_shift(texture, mlx, img, scale, size, position2);
	texture_to_image_with_shift(texture, mlx, img, scale, size, position);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	//while (1);
	/*
	while (1)
	{
		usleep(1000);
		if (scale > 8.5)
			continue;
		texture_to_image(texture, mlx, img, scale, size, position);
		mlx_put_image_to_window(mlx, win, img, 0, 0);
		scale += 0.001 * add;
		add += 0.05;
	}
	*/
}
