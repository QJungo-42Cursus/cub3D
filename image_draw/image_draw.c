#include "../cube3D.h"

void print_img_data(void *img, int img_width, int img_height)
{
	int		i;
	int		j;
	char	*data;

	printf("size of img: %d/%d\n", img_width, img_height);

	data = (char *)img;
	i = 0;
	while (i < img_height)
	{
		j = 0;
		while (j < img_width)
		{
			printf("%d ", data[i * img_width + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

typedef struct s_texture {
	t_vec2i		size;
	void		*img; // ??
}	t_texture;

/// to test image_draw
int main()
{
	void	*mlx;
	void	*img;
	t_vec2i	size;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920 / 2, 1080 / 2, "cc");
	img = mlx_xpm_file_to_image(mlx, "./textures/wood.xpm", &size.x, &size.y);


	// l'idee c'est de prendre l'image et de compresser les pixels dans l'axe y plus le cube 
	// est eloigne de nous
	// -> comme ca on a la sensation de perspective !
	// donc d'abors on mlx_xpm_file_to_image et on modifie l'image que ca nous donne !

	print_img_data(img, size.x, size.y);

	mlx_put_image_to_window(mlx, win, img, 0, 0);
	while (1);
}

