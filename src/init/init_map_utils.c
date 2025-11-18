/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:38:45 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/18 15:35:47 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void process_map_char(char c, int **map, t_data *data, int i, int j)
{
    if (c == '1' || c == ' ')
        map[i][j] = 1;
    else if (c == '0')
        map[i][j] = 0;
    else if (c == 'N')
    {
        set_player_north(data, i, j);
        map[i][j] = 0;
    }
    else if (c == 'S')
    {
        set_player_south(data, i, j);
        map[i][j] = 0;
    }
    else if (c == 'E')
    {
        set_player_east(data, i, j);
        map[i][j] = 0;
    }
    else if (c == 'W')
    {
        set_player_west(data, i, j);
        map[i][j] = 0;
    }
}

static void fill_map_line(char *line, int **map, t_data *data, int i)
{
    size_t j;

    j = 0;
    while (j < ft_strlen(line) - 1)
    {
        process_map_char(line[j], map, data, i, j);
        j++;
    }
}

static int **allocate_map(t_map_size *size)
{
    int **map;
    int i;

    map = ft_calloc(size->height, sizeof(int *));
    if (!map)
        return (NULL);
    i = 0;
    while (i < size->height)
    {
        map[i] = ft_calloc(size->width, sizeof(int));
        if (!map[i])
            return (NULL);
        i++;
    }
    return (map);
}

int **fill_map(t_map_size *size, t_data *data)
{
    int **map;
    char *line;
    int i;

    map = allocate_map(size);
    if (!map)
    {
        print_error(E_malloc);
        return (NULL);
    }
    i = 0;
    while (i < size->height)
    {
        if (data->cub_doc[i][0] == '1')
        {line = data->cub_doc[i];
        fill_map_line(line, map, data, i);
        free(line);}
        i++;
    }
    return (map);
}
