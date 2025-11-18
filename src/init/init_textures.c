/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:02:21 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/18 17:26:40 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char *extract_path(char *line, int i)
{
    int start;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    start = i;
    while (line[i] && line[i] != '\n')
        i++;
    return ft_substr(line, start, i - start);
}

void check_line(t_data *data, char *line)
{
    int i = 0;

    // skip initial spaces
    while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
        i++;

    // NORTH
    if (line[i] == 'N' && line[i+1] == 'O' &&
        (line[i+2] == ' ' || line[i+2] == '\t'))
    {
        i += 2;
        data->path_textures.NO = extract_path(line, i);
        return ;
    }
    // SOUTH
    if (line[i] == 'S' && line[i+1] == 'O' &&
        (line[i+2] == ' ' || line[i+2] == '\t'))
    {
        i += 2;
        data->path_textures.SO = extract_path(line, i);
        return ;
    }
    // WEST
    if (line[i] == 'W' && line[i+1] == 'E' &&
        (line[i+2] == ' ' || line[i+2] == '\t'))
    {
        i += 2;
        data->path_textures.WE = extract_path(line, i);
        return ;
    }
    // EAST
    if (line[i] == 'E' && line[i+1] == 'A' &&
        (line[i+2] == ' ' || line[i+2] == '\t'))
    {
        i += 2;
        data->path_textures.EA = extract_path(line, i);
        return ;
    }

    // FLOOR COLOR
    if (line[i] == 'F' && (line[i+1] == ' ' || line[i+1] == '\t'))
    {
        i++;
        data->path_textures.F = extract_path(line, i);
        return ;
    }

    // CEILING COLOR
    if (line[i] == 'C' && (line[i+1] == ' ' || line[i+1] == '\t'))
    {
        i++;
        data->path_textures.C = extract_path(line, i);
        return ;
    }
}

static void add_path_textures(t_data *data)
{
    int i;

    i = 0;
    while (data->cub_doc[i])
    {
        check_line(data, data->cub_doc[i]);
        i++;
    }
    return ;
}

void init_teximg(t_data *data, int i)
{
    int x;
    int y;

    x = 32;
    y = 32;

    if (i == 0)
        data->teximg[i].img = mlx_xpm_file_to_image(data->mlx, data->path_textures.NO, &x, &y);
    else if (i == 1)
        data->teximg[i].img = mlx_xpm_file_to_image(data->mlx, data->path_textures.SO, &x, &y);
    else if (i == 2)
        data->teximg[i].img = mlx_xpm_file_to_image(data->mlx, data->path_textures.WE, &x, &y);
    else if (i == 3)
        data->teximg[i].img = mlx_xpm_file_to_image(data->mlx, data->path_textures.EA, &x, &y);

    if (!data->teximg[i].img)
        exit_program(data, E_path);

    data->teximg[i].width = x;
    data->teximg[i].height = y;

    // 👉 Récupération du tableau de pixels
    data->teximg[i].px = (unsigned int *)mlx_get_data_addr(
        data->teximg[i].img, 
        &data->teximg[i].bpp,
        &data->teximg[i].line_len,
        &data->teximg[i].endian
    );
}


void init_textures(t_data *data)
{
    int i;

    i = 0;
    add_path_textures(data);
    init_c_colors(data);
    while (i < 4)
    {
        init_teximg(data, i);
        i++;
    }
    return ;
}
