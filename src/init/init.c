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
    data->win = mlx_new_window(data->mlx, 1500, 1000, "Cub3d");
    data->img = mlx_new_image(data->mlx, 1500, 1000);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
}

void init_struct(t_data *data, t_map_size *map_size, char *map_name)
{
    data->map = init_map(data, map_size, map_name);
    if (data->map == NULL)
        exit_program(data, Error);
    printf("%s \n%s\n", data->path_textures.C, data->path_textures.F);
}
