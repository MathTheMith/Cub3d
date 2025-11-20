/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:13:35 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/20 13:16:51 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	loop_hook(t_data *data)
{
	process_movement(data);
	draw_background(data, SCREEN_W, SCREEN_H);
	draw_wall(data, &data->p);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    //Debug
	printf("%.4f %.4f\n", data->p.p_x, data->p.p_y);
    //
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map_size	map_size;

	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		exit_program(&data, E_mlx_env);
	parsing(ac, av, &data);
	init_struct(&data, &map_size, av[1]);
	if (!check_map(&data, &map_size))
		exit_program(&data, E_map);
	init_window(&data);
	hide_mouse(&data);
	lock_mouse(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_hook(data.win, 6, 1L << 6, mouse_move, &data);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
