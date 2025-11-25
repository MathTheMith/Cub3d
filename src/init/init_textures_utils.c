/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:25:17 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/25 17:36:05 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= '\t' && line[i] <= '\r'))
		i++;
	if (!check_line_text(data, line, &i))
		return ;
	if (line[i] == 'N' && line[i + 1] == 'O'
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
	{
		i += 2;
		data->path_textures.no = extract_path(line, i);
		return ;
	}
	if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		i++;
		data->path_textures.f = extract_path(line, i);
		return ;
	}
	if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
	{
		i++;
		data->path_textures.c = extract_path(line, i);
	}
}

char	*extract_path(char *line, int i)
{
	int	start;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	return (ft_substr(line, start, i - start));
}

void	add_path_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->cub_doc[i])
	{
		check_line(data, data->cub_doc[i]);
		i++;
	}
}

void	validate_and_add_walls(char ***map, t_map_size *map_size,
									t_data *data)
{
	if (!validate_map_with_flood_fill(*map, map_size, data)
		|| data->count_player != 1)
		exit_program(data, E_map);
	*map = add_walls(data, *map, map_size);
}

bool	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}
