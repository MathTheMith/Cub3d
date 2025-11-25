/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:13:45 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:15:03 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_left(t_data *data)
{
	double	rot_speed;

	rot_speed = data->dpi * 100;
	rotate_direction(&data->p, -rot_speed);
	rotate_plane(&data->p, -rot_speed);
}

void	rotate_right(t_data *data)
{
	double	rot_speed;

	rot_speed = data->dpi * 100;
	rotate_direction(&data->p, rot_speed);
	rotate_plane(&data->p, rot_speed);
}

void	rotate_direction(t_player *p, double rot_speed)
{
	double	old_dirx;

	old_dirx = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dirx * sin(rot_speed) + p->dir_y * cos(rot_speed);
}

void	rotate_plane(t_player *p, double rot_speed)
{
	double	old_planex;

	old_planex = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_planex * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		center_x;
	int		delta;
	double	rot;

	(void)y;
	center_x = 1500 / 2;
	delta = x - data->last_mouse_x;
	if (delta != 0)
	{
		rot = delta * data->dpi;
		rotate_direction(&data->p, rot);
		rotate_plane(&data->p, rot);
		mlx_mouse_move(data->mlx, data->win, center_x, 1000 / 2);
		data->last_mouse_x = center_x;
	}
	return (0);
}
