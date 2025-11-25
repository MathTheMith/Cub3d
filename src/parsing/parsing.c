/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:24:05 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 17:50:43 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_map_textures(t_data *data, char ***textures_doc)
{
	int	start;
	int	i;

	start = find_map_start(data->cub_doc);
	*textures_doc = ft_calloc(start + 1, sizeof(char *));
	if (!*textures_doc)
		exit_program(data, E_malloc);
	i = 0;
	while (i < start)
	{
		(*textures_doc)[i] = ft_strdup(data->cub_doc[i]);
		if (!(*textures_doc)[i])
		{
			while (i > 0)
			{
				i--;
				free((*textures_doc)[i]);
			}
			free(*textures_doc);
			exit_program(data, E_malloc);
		}
		i++;
	}
	return (start);
}

void	check_textures(t_data *data)
{
	char	**textures_doc;
	int		i;
	int		len;

	textures_doc = NULL;
	len = get_map_textures(data, &textures_doc);
	are_textures(data, textures_doc);
	if (textures_doc)
	{
		i = 0;
		while (i < len)
		{
			free(textures_doc[i]);
			i++;
		}
		free(textures_doc);
		textures_doc = NULL;
	}
}

void	parsing(int ac, char **av, t_data *data, t_map_size *map_size)
{
	int	len;

	if (ac != 2)
		exit_program(data, E_nbarg);
	len = ft_strlen(av[1]);
	if (!((av[1][len - 1] == 'b') && (av[1][len - 2] == 'u') && (av[1][len
				- 3] == 'c') && (av[1][len - 4] == '.' && av[1][len - 5])))
		exit_program(data, E_ext);
	check_map(data, map_size, av[1]);
	check_textures(data);
}
