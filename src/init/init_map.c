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


void print_themap(t_data *data, t_map_size *map_size)
{
    int i = 0;

    printf("----- MAP -----\n");
    while (i < map_size->height && data->cub_doc[i])
    {
        printf("%s", data->cub_doc[i]);
        i++;
    }
    printf("---------------\n");
}

void copy_all_doc(t_data *data, char *map_name, t_map_size *map_size)
{
    int fd;
    int i;
    char *line;

    i = 0;
    data->cub_doc = calloc(map_size->height + 1, sizeof(char *));
    if (!data->cub_doc)
        return;
    open_map_file(data, map_name, &fd);
    if (fd < 0)
        return;
    line = get_next_line(fd);
    while (line && i < map_size->height)
    {
        data->cub_doc[i] = line;
        i++;
        line = get_next_line(fd);
    }
    data->cub_doc[i] = NULL;
    close(fd);
    print_themap(data, map_size);
}

void get_map_size(int fd, t_map_size *map_size)
{
    char *line;
    int tmp;

    line = get_next_line(fd);
    while (line != NULL)
    {
        tmp = ft_strlen(line);
        if (tmp > map_size->width)
            map_size->width = tmp;
        free(line);
        line = get_next_line(fd);
        map_size->height++;
    }
}

// void print_int_map(int **map, t_map_size *map_size)
// {
//     int i = 0;
//     int j = 0;
//     printf("\n----- MAP INT-----\n");
//     while (i < map_size->height)
//     {
//         j = 0;
//         while(j < map_size->width)
//         {
//             printf("%d", map[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
//     printf("---------------\n");
// }

int **init_map(t_data *data, t_map_size *map_size)
{
    int **map;
    map = fill_map(map_size, data);
    // print_int_map(map, map_size);
    return (map);
}
