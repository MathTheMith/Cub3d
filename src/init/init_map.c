/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:48:25 by marvin            #+#    #+#             */
/*   Updated: 2025/10/15 20:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_map_size get_map_size(int fd)
{
    t_map_size size;
    char *line;
    char tmp;

    size.width = 0;
    size.height = 0;
    line = get_next_line(fd);
    while (line != NULL)
    {
        tmp = ft_strlen(line);
        if (tmp > size.width)
            size.width = tmp;
        free(line);
        line = get_next_line(fd);
        size.height++;
    }
    return (size);
}

int **init_map(t_data *data, t_map_size *size, char *map_name)
{
    int fd;
    int **map;

    fd = open_map_file(map_name);
    if (fd < 0)
        return (NULL);
    *size = get_map_size(fd);
    close(fd);
    fd = open_map_file(map_name);
    if (fd < 0)
        return (NULL);
    map = fill_map(fd, size, data);
    close(fd);
    return (map);
}
