/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:59:53 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/26 10:09:02 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	transfer_cub_map(t_data *data, char *map_name)
{
	int	fd;
	int	doc_height;
	int	doc_width;

	doc_height = 0;
	doc_width = 0;
	open_map_file(data, map_name, &fd);
	if (fd < 0)
		exit_program(data, E_path);
	get_doc_size(data, fd, &doc_height, &doc_width);
	copy_all_doc(data, map_name, doc_height);
	close(fd);
}

void	check_map(t_data *data, t_map_size *map_size, char *map_name)
{
	transfer_cub_map(data, map_name);
	get_map_size(data, map_size);
	data->char_map = fill_char_map(map_size, data);
	if (!data->char_map)
		exit_program(data, E_maps);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}
