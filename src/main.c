/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:53:17 by marvin            #+#    #+#             */
/*   Updated: 2025/10/16 11:51:56 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 65362)
        move_forward(data);
    if (keycode == 65364)
        move_backward(data);
    if (keycode == 65361)
        rotate_left(data);
    if (keycode == 65363)
        rotate_right(data);
    return (0);
}

int loop_hook(t_data *data)
{
    draw_background(data->data, data->line_len, data->bpp, 1500, 1000);
    draw_wall(data, &data->p);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    
    parsing(ac, av, &data);
    init_struct(&data);
    init_window(&data);
    mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
    mlx_loop_hook(data.mlx, loop_hook, &data);
    mlx_loop(data.mlx);
    return 0;
}