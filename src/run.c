
#include <X11/X.h>
#include "cube3D.h"

/*
**  hook funct are called as follow :
**
**   expose_hook(void *param);
**   key_hook(int keycode, void *param);
**   mouse_hook(int button, int x,int y, void *param);
**   loop_hook(void *param);
**
*/


int	loop_hook(void *data)
{
	t_program *program = (t_program *)data;

	//printf("loop hook\n");
	if (!program->refresh)
		return 0;
	return 0;
}

int	close_window(void *data)
{
	t_program *program = (t_program *)data;

	program->refresh = FALSE;
	mlx_loop_end(program->mlx);
	return 0;
}

int	key_hook(int key, void *data)
{
	t_program *program = (t_program *)data;

	printf("%d\n", key);
	printf("key esc = %d\n", KEY_ESC);
	if (key == KEY_ESC)
	{
		program->refresh = FALSE;
		mlx_loop_end(program->mlx);
	}
	return 0;
}

void	run(t_program *program)
{
	mlx_do_key_autorepeaton(program->mlx);
	mlx_hook(program->win, ON_DESTROY, 0, close_window, program);
	mlx_hook(program->win, ON_KEYDOWN, 1L<<0, key_hook, program);

	//mlx_loop_hook(program->mlx, loop_hook, program);
	mlx_loop(program->mlx);
	printf("close window\n");
}

/*
void	main_loop(t_program *program)
{

	mlx_hook(program->win, ON_DESTROY, 0, close_window, NULL);
	mlx_hook(program->win, ON_KEYDOWN, 0, key_hook, NULL);
	mlx_loop(program->mlx);
}
*/
