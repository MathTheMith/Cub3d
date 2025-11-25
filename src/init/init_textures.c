/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:02:21 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 16:57:32 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_line_text(t_data *data, char *line, int *i)
{
	if (line[*i] == 'S' && line[*i + 1] == 'O'
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		*i += 2;
		data->path_textures.SO = extract_path(line, *i);
		return (0);
	}
	if (line[*i] == 'W' && line[*i + 1] == 'E'
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		*i += 2;
		data->path_textures.WE = extract_path(line, *i);
		return (0);
	}
	if (line[*i] == 'E' && line[*i + 1] == 'A'
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		*i += 2;
		data->path_textures.EA = extract_path(line, *i);
		return (0);
	}
	return (1);
}

static void	put_teximg(t_data *data, int *i)
{
	int	x;
	int	y;

	x = 32;
	y = 32;
	if (*i == 0)
		data->teximg[*i].img = mlx_xpm_file_to_image(data->mlx,
				data->path_textures.NO, &x, &y);
	else if (*i == 1)
		data->teximg[*i].img = mlx_xpm_file_to_image(data->mlx,
				data->path_textures.SO, &x, &y);
	else if (*i == 2)
		data->teximg[*i].img = mlx_xpm_file_to_image(data->mlx,
				data->path_textures.WE, &x, &y);
	else if (*i == 3)
		data->teximg[*i].img = mlx_xpm_file_to_image(data->mlx,
				data->path_textures.EA, &x, &y);
}

void	init_teximg(t_data *data, int i)
{
	put_teximg(data, &i);
	if (!data->teximg[i].img)
		exit_program(data, E_tex);
	data->teximg[i].width = 32;
	data->teximg[i].height = 32;
	data->teximg[i].px = (unsigned int *)mlx_get_data_addr(
			data->teximg[i].img,
			&data->teximg[i].bpp,
			&data->teximg[i].line_len,
			&data->teximg[i].endian);
}

void	init_textures(t_data *data)
{
	int		i;
	size_t	rgb_lenght_f;
	size_t	rgb_lenght_c;

	i = 0;
	rgb_lenght_c = 0;
	rgb_lenght_f = 0;
	add_path_textures(data);
	init_colors(data, rgb_lenght_f, rgb_lenght_c);
	while (i < 4)
	{
		init_teximg(data, i);
		i++;
	}
	return ;
}
