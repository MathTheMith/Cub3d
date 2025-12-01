/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:03:20 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/27 10:36:45 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../libft/libft.h"

static int	is_something(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] == '\n')
		return (0);
	return (1);
}

static int	is_map_a_line(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] == '1')
		return (1);
	if (j != 0)
	{
		if (line[j] == '\n' && line[j - 1] == ' ')
			return (1);
	}
	return (0);
}

static int	count_map_height(t_data *data, int start)
{
	int		i;
	int		height;

	i = start;
	height = 0;
	while (data->cub_doc[i] && is_map_a_line(data->cub_doc[i]))
	{
		height++;
		i++;
	}
	while (data->cub_doc[i])
	{
		if (is_something(data->cub_doc[i]))
			exit_program(data, E_mapc);
		i++;
	}
	return (height);
}

static int	calculate_max_width(char **cub_doc, int start)
{
	int	i;
	int	len;
	int	max_width;

	i = start;
	max_width = ft_strlen(cub_doc[i]);
	while (cub_doc[i] && is_map_a_line(cub_doc[i]))
	{
		len = ft_strlen(cub_doc[i]);
		if (len > 0 && cub_doc[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	get_map_size(t_data *data, t_map_size *map_size)
{
	int	start;

	start = find_map_start(data->cub_doc);
	if (start == -1)
		exit_program(data, E_maps);
	data->map_size.max_width = ft_strlen(data->cub_doc[start]);
	map_size->height = count_map_height(data, start);
	if (!map_size->height)
		exit_program(data, E_map);
	map_size->width = ft_calloc(map_size->height, sizeof(int));
	if (!map_size->width)
		exit_program(data, E_malloc);
	data->map_size.max_width = calculate_max_width(data->cub_doc, start);
	fill_width_array(map_size->width, map_size->height,
		data->map_size.max_width);
	data->map_size.height = map_size->height;
	data->map_size.width = map_size->width;
}
