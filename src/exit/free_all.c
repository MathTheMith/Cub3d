/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:07:51 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:08:18 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	free_textures_paths(t_data *data)
{
	if (data->path_textures.NO)
	{
		free(data->path_textures.NO);
		data->path_textures.NO = NULL;
	}
	if (data->path_textures.SO)
	{
		free(data->path_textures.SO);
		data->path_textures.SO = NULL;
	}
	if (data->path_textures.WE)
	{
		free(data->path_textures.WE);
		data->path_textures.WE = NULL;
	}
	if (data->path_textures.EA)
	{
		free(data->path_textures.EA);
		data->path_textures.EA = NULL;
	}
}

static void	free_colors_paths(t_data *data)
{
	if (data->path_textures.F)
	{
		free(data->path_textures.F);
		data->path_textures.F = NULL;
	}
	if (data->path_textures.C)
	{
		free(data->path_textures.C);
		data->path_textures.C = NULL;
	}
}

static void	free_cub_doc(t_data *data)
{
	int	i;

	if (!data->cub_doc)
		return ;
	i = 0;
	while (data->cub_doc[i])
	{
		free(data->cub_doc[i]);
		data->cub_doc[i] = NULL;
		i++;
	}
	free(data->cub_doc);
	data->cub_doc = NULL;
}

static void	free_cmap(t_data *data)
{
	int	i;

	if (data->char_map)
	{
		i = 0;
		while (i < data->map_size.height)
		{
			free(data->char_map[i]);
			i++;
		}
		free(data->char_map);
		data->char_map = NULL;
	}
}

void	free_all(t_data *data)
{
	int	i;

	if (data->map)
	{
		i = 0;
		while (i < data->map_size.height)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
	if (data->map_size.width)
		free(data->map_size.width);
	free_cmap(data);
	free_textures_paths(data);
	free_colors_paths(data);
	free_cub_doc(data);
}
