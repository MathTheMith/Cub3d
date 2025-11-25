/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:26:38 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 16:28:12 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	starts_with(const char *line, const char *token)
{
	int	len;

	len = ft_strlen(token);
	return (ft_strncmp(line, token, len) == 0);
}

static void	check_all_textures_found(t_data *data, char **textures_doc,
				int *found)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (found[j] == 0)
		{
			free_map(textures_doc);
			exit_program(data, E_tex);
		}
		j++;
	}
}

static void	mark_texture_found(t_data *data, char *line, char **tokens,
				int *found)
{
	int	j;

	j = 0;
	while (j < 6)
	{
		if (starts_with(line, tokens[j]))
		{
			if (found[j] == 1)
				exit_program(data, E_tex);
			found[j] = 1;
			break ;
		}
		j++;
	}
}

void	are_textures(t_data *data, char **textures_doc)
{
	char	*tokens[6];
	int		found[6];
	int		i;

	tokens[0] = "NO ";
	tokens[1] = "SO ";
	tokens[2] = "WE ";
	tokens[3] = "EA ";
	tokens[4] = "F ";
	tokens[5] = "C ";
	i = 0;
	while (i < 6)
		found[i++] = 0;
	i = 0;
	while (textures_doc[i])
	{
		mark_texture_found(data, textures_doc[i], tokens, found);
		i++;
	}
	check_all_textures_found(data, textures_doc, found);
}
