/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:12:56 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/25 16:29:21 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**allocate_tmp_map(t_data *data, char **map, t_map_size *map_size)
{
	char	**tmp_map;

	tmp_map = malloc(map_size->height * sizeof(char *));
	if (!tmp_map)
	{
		free_map(map);
		exit_program(data, E_malloc);
	}
	return (tmp_map);
}

static void	free_tmp_map_on_error(char **tmp_map, int lines_allocated)
{
	while (lines_allocated > 0)
	{
		lines_allocated--;
		free(tmp_map[lines_allocated]);
	}
	free(tmp_map);
}

char	*allocate_line(t_data *data, char **map, char **tmp_map, int i)
{
	char	*line;

	line = malloc((data->map_size.width[i] + 2) * sizeof(char));
	if (!line)
	{
		free_tmp_map_on_error(tmp_map, i);
		data->char_map = map;
		exit_program(data, E_malloc);
	}
	return (line);
}

void	copy_and_add_wall(char **map, char **tmp_map,
							t_map_size *map_size, int i)
{
	int	j;

	j = 0;
	while (j < map_size->width[i])
	{
		tmp_map[i][j] = map[i][j];
		j++;
	}
	free(map[i]);
	map[i] = NULL;
	tmp_map[i][j] = '1';
	tmp_map[i][j + 1] = '\0';
	map_size->width[i]++;
}

void	free_int_map_on_error(int **int_map, int lines_allocated)
{
	while (lines_allocated > 0)
	{
		lines_allocated--;
		free(int_map[lines_allocated]);
	}
	free(int_map);
}
