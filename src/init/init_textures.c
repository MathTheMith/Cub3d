/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:02:21 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/18 12:55:57 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void check_line(t_data *data, char *line)
{
    int i = 0;
    int start;

    while (line[i] == ' ' || line[i] == '\t')
        i++;

    if (line[i] == '\0' || line[i] == '\n')
        return;

    if (line[i] == 'F' && (line[i+1] == ' ' || line[i+1] == '\t'))
    {
        i++;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        start = i;
        while (line[i] && line[i] != '\n')
            i++;
        data->textures.F = ft_substr(line, start, i - start);
        return;
    }

    if (line[i] == 'C' && (line[i+1] == ' ' || line[i+1] == '\t'))
    {
        i++;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        start = i;
        while (line[i] && line[i] != '\n')
            i++;
        data->textures.C = ft_substr(line, start, i - start);
        return;
    }
}


void add_textures(t_data *data)
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

void init_textures(t_data *data)
{
    add_textures(data);
    init_c_colors(data);
    return ;
}
