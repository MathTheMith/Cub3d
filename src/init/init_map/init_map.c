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

void	copy_all_doc(t_data *data, char *map_name, int doc_height)
{
	int		fd;
	int		i;
	char	*line;

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

void	get_doc_size(t_data *data, int fd, int *doc_height, int *doc_width)
{
	char	*line;
	int		tmp;

	line = get_next_line(fd);
	if (!line)
		exit_program(data, E_map);
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

int	find_map_start(char **doc)
{
	int	i;
	int	j;

	i = 0;
	while (doc[i])
	{
		j = 0;
		while (doc[i][j] == ' ')
			j++;
		if (doc[i][j] == '1' || doc[i][j] == '0')
			return (i);
		i++;
	}
	return (-1);
}

void	fill_int_map_line(char **char_map, int **int_map,
								t_map_size *map_size, int i)
{
	int	j;

	j = 0;
	while (j < map_size->width[i])
	{
		if (char_map[i][j] == '0')
			int_map[i][j] = 0;
		else
			int_map[i][j] = 1;
		j++;
	}
}

int	**allocate_int_map(t_map_size *map_size)
{
	int	**int_map;
	int	i;

	int_map = ft_calloc(map_size->height, sizeof(int *));
	if (!int_map)
		return (NULL);
	i = 0;
	while (i < map_size->height)
	{
		int_map[i] = ft_calloc(map_size->width[i], sizeof(int));
		if (!int_map[i])
		{
			free_int_map_on_error(int_map, i);
			return (NULL);
		}
		i++;
	}
	return (int_map);
}
