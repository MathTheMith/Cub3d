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

char **duplicate_char_map(char **original, t_map_size *size)
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
        copy[i] = malloc(sizeof(char) * (size->width[i] + 1));
        if (!copy[i])
        {
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        j = 0;
        while (j < size->width[i])
        {
            copy[i][j] = original[i][j];
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    copy[size->height] = NULL;
    return (copy);
}

void transfer_cub_map(t_data *data, char *map_name)
{
    int fd;
    int doc_height;
    int doc_width;

    doc_height = 0;
    doc_width = 0;
    open_map_file(data, map_name, &fd);
    if (fd < 0)
        exit_program(data, E_path);
    get_doc_size(fd, &doc_height, &doc_width);
    copy_all_doc(data, map_name, &doc_height);
    close(fd);
}

void check_map(t_data *data, t_map_size *map_size, char *map_name)
{
	transfer_cub_map(data, map_name);
	get_map_size(data, map_size);
	data->char_map = fill_char_map(map_size, data);
	if (!data->char_map)
		exit_program(data, E_map);
}