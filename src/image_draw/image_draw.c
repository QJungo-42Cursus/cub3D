#include "../cube3D.h"
#include <math.h>

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
		*(pixel_addr(img_index.x, img_index.y + shift, &img_data)) = texture.pixels[(int)roundf(text_index.x) + (int)roundf(text_index.y) * texture.size.y];
		img_index.y++;
		text_index.y += 1.f / scale;
	}
}

void close_window(void *c)
{
	exit(1);
	(void)c;
}

void key_hook(int k, void *c)
{
	printf("%d\n", k);
	(void)c;
}

/// to test image_draw
int main()
{
	// printf("%x\n", color_from_rgb(1, 2, 3));
	// color_to_rgb(0xFF01020A, &r, &g, &b);
	
	t_vec2i		size =		{ 1600, 900 };
	void		*mlx =		mlx_init();
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_img_data	img_data =	new_img_data(mlx, size);

	mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);

	fillscreen(&img_data, color_from_rgb(10, 10, 10), color_from_rgb(100, 100, 100));

	mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);

	mlx_hook(win, ON_DESTROY, 0, close_window, NULL);
	mlx_hook(win, ON_KEYDOWN, 0, key_hook, NULL);


	mlx_loop(mlx);
}
