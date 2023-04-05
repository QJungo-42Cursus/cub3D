
#include "../cube3D.h"
#include <math.h>

typedef struct s_ray2 {
	t_vec2i	tile_pos;
	t_vec2	start_p;
	t_vec2	dir;
	t_vec2	delta_dist;
	t_vec2	dist_impact;
	t_vec2	step;
	t_vec2	len;
}	t_ray2;

void	set_ray2(t_player p, t_ray2 *ray, float angle);
void	get_impact2(t_ray2 *ray, t_map *map);

static int	is_a_wall(t_vec2i coor, t_map map)
{
	if (coor.x > map.size.x || coor.y > map.size.y)
	{
		printf("Impact out of scoop");
		return (-1);
	}
	if (coor.x < 0 || coor.y < 0)
	{
		printf("Impact out of scoop");
		return (-1);
	}
	printf("coor: %d %d", coor.x, coor.y);
	printf(" %c\n", map.tiles[coor.y][coor.x]);
	if (map.tiles[coor.y][coor.x] == WALL)
		return (1);
	else
		return (0);
}

void	ray_casting_loop(t_program *prog, t_img_data *img_data)
{
	int		x;
	t_ray2	ray;
	int		dist;

	x = -45;
	while (x < 46)
	{
		set_ray2(prog->player, &ray, (float) x);
		get_impact2(&ray, &prog->map);
		dist = sqrt((ray.len.x * ray.len.x) + (ray.len.y + ray.len.y));
		x++;
	}
}

void	set_ray2(t_player p, t_ray2 *ray, float angle)
{
	ray->tile_pos = new_vec2i((int) p.pos.x, (int) p.pos.y);
	ray->dir.x = p.dir_cam.x * cos(angle) - p.dir_cam.y * sin(angle);
	ray->dir.y = p.dir_cam.x * sin(angle) - p.dir_cam.y * cos(angle);
	if (((ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y)) != 1)
		printf("Not normelize vector");
	ray->delta_dist.x
		= sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->delta_dist.y
		= sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	ray->step = new_vec2(1, 1);
	ray->len.x = (ray->tile_pos.x + 1 - p.pos.x) * ray->delta_dist.x;
	ray->len.y = (ray->tile_pos.y + 1 - p.pos.y) * ray->delta_dist.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->len.x = (p.pos.x - ray->tile_pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->len.y = (p.pos.y - ray->tile_pos.y) * ray->delta_dist.y;
	}
	}
}

void	get_impact2(t_ray2 *ray, t_map *map)
{
	int	hit;
	int	side;
	int	status;

	hit = FALSE;
	while (hit == FALSE)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->len.x += ray->delta_dist.x;
			ray->tile_pos.x += ray->step.x;
			side = FALSE;
		}
		else
		{
			ray->len.x += ray->delta_dist.x;
			ray->tile_pos.y += ray->step.y;
			side = TRUE;
		}
		if (ray->tile_pos.x < 0 || ray->tile_pos.y < 0)
			break ;
		if (ray->tile_pos.x >= map->size.x || ray->tile_pos.y >= map->size.y)
			break ;
		status = is_a_wall(ray->tile_pos, *map);
		if (status == 1)
			hit = TRUE;
		else if (status == -1)
			break ;
	}
}
