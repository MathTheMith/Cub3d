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
    data->win = mlx_new_window(data->mlx, 1500, 1000, "Cub3D");
    if (data->win == NULL)
        exit_program(data, E_mlx_win);
    data->img = mlx_new_image(data->mlx, 1500, 1000);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
}

void transfer_cub_map(t_data *data, t_map_size *map_size, char *map_name)
{
    int fd;

    open_map_file(data, map_name, &fd);
    if (fd < 0)
        exit_program(data, E_path);
    get_map_size(fd, map_size);
    copy_all_doc(data, map_name, map_size);
    close(fd);
}

void init_struct(t_data *data, t_map_size *map_size, char *map_name)
{
    ft_memset(map_size, 0, sizeof(t_map_size));
    transfer_cub_map(data, map_size, map_name);
    init_textures(data);
    data->map = init_map(data, map_size);
    if (data->map == NULL)
        exit_program(data, Error);
    printf("%s \n%s\n", data->path_textures.C, data->path_textures.F);
}
