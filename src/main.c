/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:53:17 by marvin            #+#    #+#             */
/*   Updated: 2025/11/04 22:21:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int close_window(t_data *data)
{
    (void)data;
    exit(0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307)
        close_window(data);
    if (keycode == 119)
        move_forward(data);
    if (keycode == 115)
        move_backward(data);
    if (keycode == 97)
        move_left(data);
    if (keycode == 100)
        move_right(data);
    if (keycode == 65361)
        rotate_left(data);
    if (keycode == 65363)
        rotate_right(data);
    return (0);
}


int loop_hook(t_data *data)
{
    draw_background(data, 1500, 1000);
    draw_wall(data, &data->p);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    printf("%.4f %.4f\n", data->p.p_x, data->p.p_y);
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    t_map_size size;
    parsing(ac, av, &data);
    init_struct(&data, &size, av[1]);
    if (!check_map(&data, &size))
    {
        printf("Error\nMap validation failed");
        return (1);
    }
    init_window(&data);
    mlx_hook(data.win, 2, 1L<<0, key_hook, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop_hook(data.mlx, loop_hook, &data);
    mlx_loop(data.mlx);
    return 0;
}