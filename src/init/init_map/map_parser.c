/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:45:44 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/26 10:29:19 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	process_map_char(char c, t_data *data,
		int i, int j)
{
	int	valid_char;

	valid_char = 0;
	if (c == ' ' || c == '1' || c == '0')
	{
		data->char_map[i][j] = c;
		valid_char++;
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->char_map[i][j] = '0';
		valid_char++;
		data->count_player++;
	}
	if (valid_char == 0)
		exit_program(data, E_map);
}

char	**allocate_char_map(t_map_size *map_size)
{
	char	**map;
	int		i;

	map = ft_calloc(map_size->height + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < map_size->height)
	{
		map[i] = ft_calloc(map_size->width[i] + 1, sizeof(char));
		if (!map[i])
		{
			while (i > 0)
			{
				i--;
				free(map[i]);
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	fill_map_line(char *line, t_data *data, int i)
{
	int	j;
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	j = 0;
	while (j < data->map_size.width[i])
	{
		if (j < len)
		{
			process_map_char(line[j], data, i, j);
			if (line[j] == 'N')
				set_player_north(data, i, j);
			else if (line[j] == 'S')
				set_player_south(data, i, j);
			else if (line[j] == 'E')
				set_player_east(data, i, j);
			else if (line[j] == 'W')
				set_player_west(data, i, j);
		}
		j++;
	}
}

int	**convert_char_to_int_map(char **char_map, t_map_size *map_size)
{
	int	**int_map;
	int	i;

	int_map = allocate_int_map(map_size);
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < map_size->height)
	{
		fill_int_map_line(char_map, int_map, map_size, i);
		i++;
	}
	return (int_map);
}

char	**add_walls(t_data *data, char **map, t_map_size *map_size)
{
	int		i;
	char	**tmp_map;

	tmp_map = allocate_tmp_map(data, map, map_size);
	i = 0;
	while (i < map_size->height)
	{
		tmp_map[i] = allocate_line(data, map, tmp_map, i);
		copy_and_add_wall(map, tmp_map, map_size, i);
		i++;
	}
	free(map);
	map = NULL;
	return (tmp_map);
}
