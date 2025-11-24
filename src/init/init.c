/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:30:24 by marvin            #+#    #+#             */
/*   Updated: 2025/10/15 23:30:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void open_map_file(t_data *data, char *map_name, int *fd)
{
    *fd = open(map_name, O_RDONLY);
    if (*fd < 0)
    {
        data->map = NULL;
        exit_program(data, E_path);
    }
}

void init_window(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
    if (data->win == NULL)
        exit_program(data, E_mlx_win);
    data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
}

void init_struct(t_data *data, t_map_size *map_size, char ***char_map_out)
{
	data->map = convert_char_to_int_map(*char_map_out, map_size);
	if (!data->map)
	{
		free_map(*char_map_out);
		exit_program(data, E_map);
	}
	init_textures(data);
	data->last_mouse_x = SCREEN_W / 2;
	data->dpi = M_DPI;
	printf("%s \n%s\n", data->path_textures.C, data->path_textures.F);
}
