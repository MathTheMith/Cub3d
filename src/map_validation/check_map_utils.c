/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:21:32 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/18 13:23:43 by mvachon          ###   ########.fr       */
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