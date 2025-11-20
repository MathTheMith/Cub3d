/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:38:45 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/20 15:00:53 by mvachon          ###   ########.fr       */
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

static void fill_map_line(char *line, int **map, t_data *data, int i, int width)
{
    int j;
    int line_len;

    line_len = ft_strlen(line);
    if (line_len > 0 && line[line_len - 1] == '\n')
        line_len--;
    
    j = 0;
    while (j < width)
    {
        if (j < line_len)
            process_map_char(line[j], map, data, i, j);
        else
            map[i][j] = 1;  // Remplir le reste avec des murs si nécessaire
        j++;
    }
}

static int **allocate_map(t_map_size *map_size)
{
    int **map;
    int i;

    map = ft_calloc(map_size->height + 1, sizeof(int *));
    if (!map)
        return (NULL);
    i = 0;
    while (i < map_size->height)
    {
        map[i] = ft_calloc(map_size->width[i], sizeof(int));
        if (!map[i])
            return (NULL);
        i++;
    }
    return (map);
}

bool check_map_line(char *line, int start_end)
{
    int i;
    int len;
    
    i = 0;
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        len--;
    
    if (start_end)
    {
        while(i < len)
        {
            if (line[i] != '1' && line[i] != ' ')
                return (0);
            i++;
        }
        return (1);
    }
    
    // Vérifier premier caractère non-espace
    while (i < len && line[i] == ' ')
        i++;
    if (i >= len || line[i] != '1')
        return (0);
    
    // Vérifier dernier caractère non-espace
    i = len - 1;
    while (i >= 0 && line[i] == ' ')
        i--;
    if (i < 0 || line[i] != '1')
        return (0);
    
    return (1);
}

int **fill_map(t_map_size *map_size, t_data *data)
{
    int i;
    int **map;
    int start;
    char *line;
    int start_end;
    
    i = 0;
    map = allocate_map(map_size);
    if (!map)
        return NULL;
    start = find_map_start(data->cub_doc);
    while (i < map_size->height)
    {
        start_end = 0;
        line = data->cub_doc[start + i];
        
        if (i == 0 || i == map_size->height - 1)
            start_end = 1;
        if (check_map_line(line, start_end) == 0)
            exit_program(data, E_map);
            
        fill_map_line(line, map, data, i, map_size->width[i]);
        i++;
    }
    return map;
}