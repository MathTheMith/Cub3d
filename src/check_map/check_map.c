/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:27:59 by marvin            #+#    #+#             */
/*   Updated: 2025/10/31 15:27:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int flood_fill(char **map, int x, int y, t_map_size *size)
{
    if (x < 0 || y < 0 || x >= size->width || y >= size->height)
        return (0);
    if (map[y][x] == '1' || map[y][x] == 'F')
        return (1);
    if (map[y][x] == ' ')
        return (0);
    map[y][x] = 'F';
    if (!flood_fill(map, x + 1, y, size))
        return (0);
    if (!flood_fill(map, x - 1, y, size))
        return (0);
    if (!flood_fill(map, x, y + 1, size))
        return (0);
    if (!flood_fill(map, x, y - 1, size))
        return (0);
    
    return (1);
}

void print_map(char **map, t_map_size *map_size)
{
    int i = 0;
    int j = 0;
    printf("\n----- MAP -----\n");
    while (i < map_size->height)
    {
        j = 0;
        while(j < map_size->width)
        {
            printf("%c", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("---------------\n");
}

int check_map(t_data *data, t_map_size *size)
{
    char    **map_copy;
    int     result;

    map_copy = duplicate_map(data, size);
    if (!map_copy)
        return (0);
    print_map(map_copy, size);
    result = flood_fill(map_copy, (int)data->p.p_x, (int)data->p.p_y, size);
    free_map(map_copy);
    return (result);
}