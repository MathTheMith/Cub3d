/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:53:42 by mvachon           #+#    #+#             */
/*   Updated: 2025/10/16 12:16:41 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void free_map(int **map)
{
    int i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void free_data_and_quit(t_data *data)
{
    (void)data;
    exit(1);
}