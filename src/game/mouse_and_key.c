/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:05:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/24 16:32:46 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <X11/keysym.h>

int	close_window(t_data *data)
{
	exit_program(data, No_error);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key[KEY_W] = 1;
	if (keycode == XK_a)
		data->key[KEY_A] = 1;
	if (keycode == XK_s)
		data->key[KEY_S] = 1;
	if (keycode == XK_d)
		data->key[KEY_D] = 1;
	if (keycode == XK_Right)
		data->key[KEY_Ra] = 1;
	if (keycode == XK_Left)
		data->key[KEY_La] = 1;
	if (keycode == XK_Shift_L)
		data->key[KEY_SHIFT] = 1;
	if (keycode == XK_Escape)
		close_window(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->key[KEY_W] = 0;
	if (keycode == XK_a)
		data->key[KEY_A] = 0;
	if (keycode == XK_s)
		data->key[KEY_S] = 0;
	if (keycode == XK_d)
		data->key[KEY_D] = 0;
	if (keycode == XK_Right)
		data->key[KEY_Ra] = 0;
	if (keycode == XK_Left)
		data->key[KEY_La] = 0;
	if (keycode == XK_Shift_L)
		data->key[KEY_SHIFT] = 0;
	return (0);
}
