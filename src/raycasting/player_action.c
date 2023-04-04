/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:28:37 by agonelle          #+#    #+#             */
/*   Updated: 2023/04/04 15:35:12 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"
#include <math.h>

typedef struct s_player {
	t_vec2	pos;
	t_vec2	dir_cam;
	t_vec2	cam_plan;
}	t_player;

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
