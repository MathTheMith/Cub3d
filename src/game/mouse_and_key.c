/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_and_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:05:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/20 13:16:57 by tfournie         ###   ########.fr       */
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
	if (keycode == XK_Shift_L)
		data->key[KEY_SHIFT] = 0;
	return (0);
}

void	hide_mouse(t_data *data)
{
	t_xvar		*xvar;
	t_win_list	*xwin;
	Display		*disp;
	Window		win;
	Pixmap		blank;
	XColor		dummy;
	char		data_bits[1] = {0};
	Cursor		cursor;

	xvar = (t_xvar *)data->mlx;
	xwin = (t_win_list *)data->win;
	disp = xvar->display;
	win = xwin->window;
	blank = XCreateBitmapFromData(disp, win, data_bits, 1, 1);
	cursor = XCreatePixmapCursor(disp, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(disp, win, cursor);
	XFreeCursor(disp, cursor);
	XFreePixmap(disp, blank);
}

void	lock_mouse(t_data *data)
{
	t_xvar		*xvar;
	t_win_list	*xwin;
	Display		*disp;
	Window		win;

	xvar = (t_xvar *)data->mlx;
	xwin = (t_win_list *)data->win;
	disp = xvar->display;
	win = xwin->window;
	XGrabPointer(disp, win, True, PointerMotionMask, GrabModeAsync,
		GrabModeAsync, win, None, CurrentTime);
}
