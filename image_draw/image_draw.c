#include "../cube3D.h"
#include <math.h>

typedef struct s_texture {
	t_vec2i			size;
	unsigned int	*pixels;
}	t_texture;

t_texture	new_texture(void *mlx, char *texture_path)
{
	t_texture	texture;
	int			x;
	int			y;
	int			bpp;
	int			size_line;
	int			endian;
	char		*data;
	void		*img_ptr;

	img_ptr = mlx_xpm_file_to_image(mlx, texture_path, &texture.size.x, &texture.size.y);
	texture.pixels = malloc(sizeof(unsigned int) * texture.size.x * texture.size.y);
	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	x = 0;
	while (x < texture.size.x)
	{
		y = 0;
		while (y < texture.size.y)
		{
			texture.pixels[x + y * texture.size.y]
				= *(unsigned int*)&data[(y * size_line) + x * (bpp / 8)];
			y++;
		}
		x++;
	}
	mlx_destroy_image(mlx, img_ptr);
	return (texture);
}

void	texture_to_image(t_texture texture, void *mlx, void *img, float scale, t_vec2i img_size)
{
	int			bpp;
	int			size_line;
	int			endian;
	char		*data;
	t_vec2i		img_index;
	t_vec2		text_index;

	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	img_index.x = 0;
	text_index.x = 0;
	while (img_index.x < texture.size.x * scale)
	{
		img_index.y = 0;
		text_index.y = 0;
		while (img_index.y < (texture.size.y - 1) * scale) // le -1 pour eviter les vieux pixels multi color en bas...
		{
			*(unsigned int*)&data[(img_index.y * size_line) + img_index.x * (bpp / 8)] = 

			texture.pixels[(int)roundf(text_index.x) + (int)roundf(text_index.y) * texture.size.y];

			img_index.y++;
			text_index.y += 1.f / scale;
		}
		img_index.x++;
		text_index.x += 1.f / scale;
	}
}

/// to test image_draw
int main()
{
	void	*mlx;
	void	*win;
	t_vec2i	size = { 1920 / 2, 1080 / 2 };

	mlx = mlx_init();
	win = mlx_new_window(mlx, size.x, size.y, "cc");

	t_texture texture = new_texture(mlx, "./textures/wood.xpm");
	void	*img = mlx_new_image(mlx, size.x, size.y);
	void	*blank_img = mlx_new_image(mlx, size.x, size.y);

	float scale = 0;
	float add = 0.1;
	while (1)
	{
		usleep(1000);
		if (scale > 8.5)
			continue;
		texture_to_image(texture, mlx, img, scale, size);
		mlx_put_image_to_window(mlx, win, img, 0, 0);
		scale += 0.001 * add;
		add += 0.05;

	}
}
