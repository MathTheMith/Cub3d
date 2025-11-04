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

void check_line(t_data *data, char *line)
{
    int i;
    int start;

    i = 0;
    while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
        i++;
    
    if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
    {
        i++;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        start = i;
        while (line[i] && line[i] != '\n')
            i++;
        data->textures.F = ft_substr(line, start, i - start);
    }
    else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
    {
        i++;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        start = i;
        while (line[i] && line[i] != '\n')
            i++;
        data->textures.C = ft_substr(line, start, i - start);
    }
}

void add_textures(t_data *data, int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
        check_line(data, line);
        free(line);
        line = get_next_line(fd);
    }
    return ;
}

void init_textures(t_data *data, char *map_name)
{
    int fd;
    fd = open_map_file(map_name);
    if (fd < 0)
        exit_program(data, E_malloc);
    add_textures(data, fd);
    close(fd);
    return ;
}

void init_struct(t_data *data, t_map_size *size, char *map_name)
{
    data->map = transfer_map(data, size, map_name);
    init_textures(data, map_name);
    printf("%s \n%s\n", data->textures.C, data->textures.F);
}

void init_window(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, 1500, 1000, "Cub3d");
    data->img = mlx_new_image(data->mlx, 1500, 1000);
    data->data = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
}