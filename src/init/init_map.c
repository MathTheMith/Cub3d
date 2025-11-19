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

void copy_all_doc(t_data *data, char *map_name, int *doc_height)
{
    int fd;
    int i;
    char *line;

    i = 0;
    data->cub_doc = calloc(*doc_height + 1, sizeof(char *));
    if (!data->cub_doc)
        return;
    open_map_file(data, map_name, &fd);
    if (fd < 0)
        return;
    line = get_next_line(fd);
    while (line && i < *doc_height)
    {
        data->cub_doc[i] = line;
        i++;
        line = get_next_line(fd);
    }
    data->cub_doc[i] = NULL;
    close(fd);
}

void get_doc_size(int fd, int *doc_height, int *doc_width)
{
    char *line;
    int tmp;


    line = get_next_line(fd);
    while (line != NULL)
    {
        tmp = ft_strlen(line);
        if (tmp > *doc_width)
            *doc_width = tmp;
        free(line);
        line = get_next_line(fd);
        (*doc_height)++;
    }
}

int find_map_start(char **doc)
{
    int i = 0;
    while (doc[i])
    {
        int j = 0;
        while (doc[i][j] == ' ')
            j++;
        if (doc[i][j] == '1' || doc[i][j] == '0')
            return i;
        i++;
    }
    return -1;
}
int is_map_line(char *line)
{
    int j = 0;
    while (line[j] == ' ')
        j++;
    return (line[j] == '1' || line[j] == '0');
}

void get_map_size(t_data *data, t_map_size *map_size)
{
    int start;
    int i;
    int len;

    len = 0;
    start = find_map_start(data->cub_doc);
    i = start;
    while (data->cub_doc[i] && is_map_line(data->cub_doc[i]))
    {
        len = ft_strlen(data->cub_doc[i]);
        if (len > map_size->width)
            map_size->width = len;
        map_size->height++;
        i++;
    }
    data->map_size.height = map_size->height;
    data->map_size.width = map_size->width;
}

void print_int_map(int **map, t_map_size *map_size)
{
    int i, j;

    printf("\n----- MAP INT -----\n");
    for (i = 0; i < map_size->height; i++)
    {
        for (j = 0; j < map_size->width; j++)
        {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
}

int **init_map(t_data *data, t_map_size *map_size)
{
    int **map;
    get_map_size(data, map_size);
    map = fill_map(map_size, data);
    print_int_map(map, map_size);
    return (map);
}
