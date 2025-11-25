/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:02:19 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:12:39 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_forward(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	if ((data->key[KEY_W] && data->key[KEY_A]) || (data->key[KEY_W]
			&& data->key[KEY_D]))
		speed /= 1.414;
	new_x = data->p.p_x + data->p.dir_x * speed;
	new_y = data->p.p_y + data->p.dir_y * speed;
	if (data->map[(int)new_y][(int)new_x] == 0)
	{
		data->p.p_x = new_x;
		data->p.p_y = new_y;
	}
}

void	move_backward(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	if ((data->key[KEY_S] && data->key[KEY_A]) || (data->key[KEY_S]
			&& data->key[KEY_D]))
		speed /= 1.414;
	new_x = data->p.p_x - data->p.dir_x * speed;
	new_y = data->p.p_y - data->p.dir_y * speed;
	if (data->map[(int)new_y][(int)new_x] == 0)
	{
		data->p.p_x = new_x;
		data->p.p_y = new_y;
	}
}

void	move_left(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	if ((data->key[KEY_W] && data->key[KEY_A]) || (data->key[KEY_S]
			&& data->key[KEY_A]))
		speed /= 1.414;
	new_x = data->p.p_x + data->p.dir_y * speed;
	new_y = data->p.p_y - data->p.dir_x * speed;
	if (data->map[(int)new_y][(int)new_x] == 0)
	{
		data->p.p_x = new_x;
		data->p.p_y = new_y;
	}
}

void	move_right(t_data *data, double speed)
{
	double	new_x;
	double	new_y;

	if ((data->key[KEY_W] && data->key[KEY_D]) || (data->key[KEY_S]
			&& data->key[KEY_D]))
		speed /= 1.414;
	new_x = data->p.p_x - data->p.dir_y * speed;
	new_y = data->p.p_y + data->p.dir_x * speed;
	if (data->map[(int)new_y][(int)new_x] == 0)
	{
		data->p.p_x = new_x;
		data->p.p_y = new_y;
	}
}

void	process_movement(t_data *data)
{
	double	speed;

	speed = data->p.p_speed;
	if (data->key[KEY_SHIFT])
		speed *= 2;
	if (data->key[KEY_W])
		move_forward(data, speed);
	if (data->key[KEY_S])
		move_backward(data, speed);
	if (data->key[KEY_A])
		move_left(data, speed);
	if (data->key[KEY_D])
		move_right(data, speed);
	if (data->key[KEY_La])
		rotate_left(data);
	if (data->key[KEY_Ra])
		rotate_right(data);
}
