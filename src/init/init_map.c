/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:48:25 by marvin            #+#    #+#             */
/*   Updated: 2025/11/20 15:00:00 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void copy_all_doc(t_data *data, char *map_name, int doc_height)
{
    int fd;
    int i;
    char *line;

    i = 0;
    data->cub_doc = ft_calloc(doc_height + 1, sizeof(char *));
    if (!data->cub_doc)
        exit_program(data, E_malloc);
    open_map_file(data, map_name, &fd);
    line = get_next_line(fd);
    while (line && i < doc_height)
    {
        data->cub_doc[i] = line;
        i++;
        line = get_next_line(fd);
    }
    if (line)
        free(line);
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
        if (line)
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
int is_map_a_line(char *line)
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
    int map_idx;

    start = find_map_start(data->cub_doc);
    i = start;
    
    while (data->cub_doc[i] && is_map_a_line(data->cub_doc[i]))
    {
        map_size->height++;
        i++;
    }
    
    map_size->width = ft_calloc(map_size->height, sizeof(int));
    if (!map_size->width)
        exit_program(data, E_malloc);
    
    i = start;
    map_idx = 0;
    while (data->cub_doc[i] && is_map_a_line(data->cub_doc[i]))
    {
        len = ft_strlen(data->cub_doc[i]);
        if (len > 0 && data->cub_doc[i][len - 1] == '\n')
            len--;
        map_size->width[map_idx] = len;
        map_idx++;
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
        for (j = 0; j < map_size->width[i]; j++)
        {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
}
