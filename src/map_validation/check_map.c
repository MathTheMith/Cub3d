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

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char **duplicate_map(t_data *data, t_map_size *size)
{
    int     i;
    int     j;
    char    **copy;

    copy = malloc(sizeof(char *) * (size->height + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < size->height)
    {
        copy[i] = malloc(sizeof(char) * (size->width + 1));
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        j = 0;
        while (j < size->width)
        {
            copy[i][j] = (data->map[i][j] == 0) ? '0' : '1';
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    copy[size->height] = NULL;
    return (copy);
}

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

int check_map(t_data *data, t_map_size *size)
{
    char    **map_copy;
    int     result;

    map_copy = duplicate_map(data, size);
    if (!map_copy)
        return (0);
    
    result = flood_fill(map_copy, (int)data->p.p_x, (int)data->p.p_y, size);
    free_map(map_copy);
    
    return (result);
}