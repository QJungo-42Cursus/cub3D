/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:28:37 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/04 18:31:52 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

void	rotate_cam(t_player *player, double angle)
{
	double	old_dir_cam;
	double	old_cam_planx;

	old_dir_cam = player->dir_cam.x;
	player->dir_cam.x = player->dir_cam.x * cos(angle)
		- player->dir_cam.y * sin(angle);
	player->dir_cam.y = old_dir_cam * sin(angle)
		+ player->dir_cam.y * cos(angle);
	old_cam_planx = player->cam_plan.x;
	player->cam_plan.x = player->cam_plan.x * cos(angle)
		- player->cam_plan.y * sin(angle);
	player->cam_plan.y = old_cam_planx * sin(angle)
		+ player->cam_plan.y * cos(angle);
}

void	set_player_cam(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir_cam = new_vec2(0, -1);
		player->cam_plan.x = 1;
		player->cam_plan.y = 0;
	}
	else if (c == 'S')
	{
		player->dir_cam = new_vec2(0, 1);
		player->cam_plan.x = -1;
		player->cam_plan.y = 0;
	}
	else if (c == 'E')
	{
		player->dir_cam = new_vec2(1, 0);
		player->cam_plan.x = 0;
		player->cam_plan.y = -1;
	}
	else
	{
		player->dir_cam = new_vec2(-1, 0);
		player->cam_plan.x = 0;
		player->cam_plan.y = 1;
	}
}

t_vec2	vec2_from_angle(double angle)
{
	t_vec2	res;

	res = new_vec2(0, 0);
	(void)angle;
	return (res);
}
