/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:42:20 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/25 16:42:20 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parse_color_component(char **str, size_t *rgb_lenght, bool last)
{
	int	value;

	value = 0;
	if (!ft_isdigit(**str))
		return (-1);
	while (**str && ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
		*rgb_lenght += 1;
	}
	if (**str == ',' && last == 0)
	{
		(*str)++;
		*rgb_lenght += 1;
	}
	return (value);
}

void	open_map_file(t_data *data, char *map_name, int *fd)
{
	*fd = open(map_name, O_RDONLY);
	if (*fd < 0)
	{
		data->map = NULL;
		exit_program(data, E_path);
	}
}

void	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, 1500, 1000, "Cub3D");
	if (data->win == NULL)
		exit_program(data, E_mlx_win);
	data->img = mlx_new_image(data->mlx, 1500, 1000);
	data->data = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
}

void	init_struct(t_data *data, t_map_size *map_size, char ***char_map_out)
{
	data->map = convert_char_to_int_map(*char_map_out, map_size);
	if (!data->map)
	{
		free_map(*char_map_out);
		exit_program(data, E_map);
	}
	init_textures(data);
	data->last_mouse_x = 1500 / 2;
	data->dpi = 0.0006;
}
