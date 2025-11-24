/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:52:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/24 13:20:26 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int starts_with(const char *line, const char *token)
{
	int len = ft_strlen(token);
	return (ft_strncmp(line, token, len) == 0);
}


void are_textures(t_data *data, char **textures_doc)
{
	char *tokens[6];
	int found[6];
	int j;
	int i;

	tokens[0] = "NO ";
	tokens[1] = "SO ";
	tokens[2] = "WE ";
	tokens[3] = "EA ";
	tokens[4] = "F ";
	tokens[5] = "C ";

	i = 0;
	while (i < 6)
	{
		found[i] = 0;
		i++;
	}
	i = 0;
	while (textures_doc[i])
	{
		j = 0;
		while (j < 6)
		{
			if (starts_with(textures_doc[i], tokens[j]))
			{
				if (found[j] == 1)
					exit_program(data, E_tex);
				found[j] = 1;
				break;
			}
			j++;
		}
		i++;
	}

	j = 0;
	while (j < 6)
	{
		if (found[j] == 0)
			exit_program(data, E_tex);
		j++;
	}
}
void get_map_textures(t_data *data, char ***cub_map)
{
    int start;
    int i;

    start = find_map_start(data->cub_doc);

    *cub_map = malloc(sizeof(char *) * start + 1);
    if (!*cub_map)
        return;

    i = 0;
    while (i < start)
    {
        (*cub_map)[i] = ft_strdup(data->cub_doc[i]);
        printf("%s", (*cub_map)[i]);
        i++;
    }
	(*cub_map)[i] = NULL;
}

void check_textures(t_data *data)
{
    char **textures_doc;
    get_map_textures(data, &textures_doc);
	are_textures(data, textures_doc);
}


void parsing(int ac, char **av, t_data *data, t_map_size *map_size)
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
