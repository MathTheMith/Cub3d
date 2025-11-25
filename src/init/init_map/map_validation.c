/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:43:34 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/25 16:56:38 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	flood_fill1(char **map, int i, int j, t_map_size *map_size)
{
	if (i < 0 || j < 0 || i >= map_size->height || j >= map_size->width[i])
		return (false);
	if (map[i][j] == '1')
		return (true);
	if (map[i][j] == 'V')
		return (true);
	if (map[i][j] == ' ')
		return (false);
	if (map[i][j] == '0')
	{
		map[i][j] = 'V';
		if (!flood_fill1(map, i - 1, j, map_size))
			return (false);
		if (!flood_fill1(map, i + 1, j, map_size))
			return (false);
		if (!flood_fill1(map, i, j - 1, map_size))
			return (false);
		if (!flood_fill1(map, i, j + 1, map_size))
			return (false);
		return (true);
	}
	return (false);
}

void	restore_visited_cells(char **map, t_map_size *map_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_size->height)
	{
		j = 0;
		while (j < map_size->width[i])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

bool	validate_map_with_flood_fill(char **map, t_map_size *map_size,
		t_data *data)
{
	int	i;
	int	j;

	(void)data;
	i = 0;
	while (i < map_size->height)
	{
		j = 0;
		while (j < map_size->width[i])
		{
			if (map[i][j] == '0')
			{
				if (!flood_fill1(map, i, j, map_size))
				{
					restore_visited_cells(map, map_size);
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	restore_visited_cells(map, map_size);
	return (true);
}

static char	**allocate_and_fill_map(t_map_size *map_size, t_data *data,
									int start)
{
	char	**map;
	char	*line;
	int		i;

	map = allocate_char_map(map_size);
	if (!map)
		exit_program(data, E_malloc);
	i = 0;
	while (i < map_size->height)
	{
		line = data->cub_doc[start + i];
		data->char_map = map;
		fill_map_line(line, data, i);
		i++;
	}
	return (map);
}

char	**fill_char_map(t_map_size *map_size, t_data *data)
{
	int		start;
	char	**map;

	start = find_map_start(data->cub_doc);
	if (start == -1)
		return (NULL);
	map = allocate_and_fill_map(map_size, data, start);
	validate_and_add_walls(&map, map_size, data);
	return (map);
}
