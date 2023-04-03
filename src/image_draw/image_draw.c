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


int close_window(void *c)
{
	exit(0);
	(void)c;
	return 0;
}

int key_hook(int k, void *c)
{
	printf("%d\n", k);
	mlx_destroy_window(c, c);
	(void)c;
	return 0;
}

int loop_hook(void *c)
{
	static int i = 0;
	(void)c;
	printf("loop %d\n", i++);
	return 0;
}

void	test1();

/// to test image_draw
int main()
{
	//test1();
	t_vec2i		size =		{ 720, 480 };
	void		*mlx =		mlx_init();
	void		*win =		mlx_new_window(mlx, size.x, size.y, "cc");
	t_img_data	img_data =	new_img_data(mlx, size);

	fillscreen(&img_data, color_from_rgb(200, 200, 200), color_from_rgb(0, 255, 255));
	mlx_put_image_to_window(mlx, win, img_data.img, 0, 0);
	mlx_hook(win, ON_DESTROY, 0, close_window, NULL);
	mlx_key_hook(win, key_hook, NULL);
	//mlx_loop_hook(mlx, loop_hook, NULL);
	mlx_loop(mlx);
}
