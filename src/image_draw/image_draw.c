#include "../cube3D.h"
#include <math.h>

int	pixel_index(int x, int y, t_img_data img_data)
{
	int		i;

	i = y * img_data.line_length;
	i += x * (img_data.bpp / 8);
	return (i);
}

unsigned int	*pixel_addr(int x, int y, t_img_data img_data)
{
	int		i;

	i = pixel_index(x, y, img_data);
	return ((unsigned int*)&img_data.addr[i]);
}

// texture (ou juste la ligne en question...)
// img_data
// position de la ligne dans l'image (en x, en y tout part du milieu)
// position en x de la texture ou pourcentage
// hauteur de la ligne

typedef struct s_texture_line {
	// alternative a cette struct
	//		-> t_texture a un **int, avec les column dans le 2eme pointeurs
	//		-> comme ca on peut passer juste le bon pointeur
	t_texture	texture;
	char		poucentage; // de 0 a 100, la position
	int			line;		// valeur en x de la ligne, equivalent au pourcentage
}	t_texture_line;

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
		*(pixel_addr(img_index.x, img_index.y + shift, img_data)) = texture.pixels[(int)roundf(text_index.x) + (int)roundf(text_index.y) * texture.size.y];
		img_index.y++;
		text_index.y += 1.f / scale;
	}
}

/// to test image_draw
int main()
{
	void		*mlx =		mlx_init();
	t_vec2i		size =		{ 1920, 1080 };
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_texture	texture =	new_text(mlx, "../textures/wood.xpm");
	void		*img =		mlx_new_image(mlx, size.x, size.y);
	t_img_data	img_data =	img_data_from(img);
	if (texture.pixels == NULL)
		return (0);
	text_column_to_img(texture, img_data, 0, 0, 5, 50);
	text_column_to_img(texture, img_data, 1, 3, 5.5, 40);
	text_column_to_img(texture, img_data, 2, 6, 6, 30);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	while (1)
	{
	}
}
