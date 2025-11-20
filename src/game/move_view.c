/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:02:42 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/20 13:02:42 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void rotate_direction(t_player *p, double rotSpeed)
{
    double oldDirX;

    oldDirX = p->dir_x;
    p->dir_x = p->dir_x * cos(rotSpeed) - p->dir_y * sin(rotSpeed);
    p->dir_y = oldDirX * sin(rotSpeed) + p->dir_y * cos(rotSpeed);
}

void rotate_plane(t_player *p, double rotSpeed)
{
    double oldPlaneX;

    oldPlaneX = p->plane_x;
    p->plane_x = p->plane_x * cos(rotSpeed) - p->plane_y * sin(rotSpeed);
    p->plane_y = oldPlaneX * sin(rotSpeed) + p->plane_y * cos(rotSpeed);
}

void rotate_left(t_data *data)
{
    double rotSpeed;

    rotSpeed = 0.07;
    rotate_direction(&data->p, -rotSpeed);
    rotate_plane(&data->p, -rotSpeed);
}

void rotate_right(t_data *data)
{
    double rotSpeed;

    rotSpeed = 0.07;
    rotate_direction(&data->p, rotSpeed);
    rotate_plane(&data->p, rotSpeed);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		center_x;
	int		delta;
	double	rot;

	(void)y;
	center_x = SCREEN_W / 2;
	delta = x - data->last_mouse_x;
	if (delta != 0)
	{
		rot = delta * data->dpi;
		rotate_direction(&data->p, rot);
		rotate_plane(&data->p, rot);
		mlx_mouse_move(data->mlx, data->win, center_x, SCREEN_H / 2);
		data->last_mouse_x = center_x;
	}
	return (0);
}
