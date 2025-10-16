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

int open_map_file(void)
{
    int fd;

    fd = open("map/map.cub", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return (-1);
    }
    return (fd);
}

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

int **allocate_map(t_map_size size, t_data *data)
{
    int **map;
    int i;

    (void)data;
    map = ft_calloc(size.height, sizeof(int *));
    if (!map)
        return (NULL);
    i = 0;
    while (i < size.height)
    {
        map[i] = ft_calloc(size.width - 1, sizeof(int));
        if (!map[i])
        {
            free_map(map);
            exit(0);
        }
        i++;
    }
    return (map);
}

void process_map_char(char c, int **map, t_data *data, int i, int j)
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

void fill_map_line(char *line, int **map, t_data *data, int i)
{
    size_t j;

    j = 0;
    while (j < ft_strlen(line) - 1)
    {
        process_map_char(line[j], map, data, i, j);
        j++;
    }
}

int **fill_map(int fd, t_map_size size, t_data *data)
{
    int **map;
    char *line;
    int i;

    map = allocate_map(size, data);
    if (!map)
        return (NULL);
    i = 0;
    while (i < size.height)
    {
        line = get_next_line(fd);
        fill_map_line(line, map, data, i);
        free(line);
        i++;
    }
    return (map);
}

int **transfer_map(t_data *data)
{
    int fd;
    t_map_size size;
    int **map;

    fd = open_map_file();
    size = get_map_size(fd);
    close(fd);
    fd = open_map_file();
    map = fill_map(fd, size, data);
    close(fd);
    return (map);
}