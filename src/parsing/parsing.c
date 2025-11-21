/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:52:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/21 14:19:36 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void check_map2(t_data *data, t_map_size *map_size, char *map_name)
{
	transfer_cub_map(data, map_name);
	get_map_size(data, map_size);
	data->char_map = fill_char_map(map_size, data);
	if (!data->char_map)
		exit_program(data, E_map);
}

void parsing(int ac, char **av, t_data *data, t_map_size *map_size)
{
	int	len;

	if (ac != 2)
		exit_program(data, E_nbarg);
	len = ft_strlen(av[1]);
	if (!((av[1][len - 1] == 'b') && (av[1][len - 2] == 'u') && (av[1][len
				- 3] == 'c') && (av[1][len - 4] == '.')))
		exit_program(data, E_ext);
	check_map2(data, map_size, av[1]);
}
