/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:02:21 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/17 18:00:25 by tfournie         ###   ########.fr       */
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
        exit_program(data, Error);
    add_textures(data, fd);
    init_c_colors(data);
    close(fd);
    return ;
}
