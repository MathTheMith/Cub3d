/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:42:30 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/25 19:03:27 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	validate_and_parse_color(t_data *data, t_color_init *params)
{
	*(params->color_value) = parse_color_component(params->color_str,
			params->rgb_length, params->is_last);
	if (*(params->color_value) < 0 || *(params->color_value) > 255)
		exit_program(data, E_tex);
}

static void	parse_ceiling_colors(t_data *data, t_color_init *params)
{
	params->color_value = &data->colors.rc;
	params->is_last = 0;
	validate_and_parse_color(data, params);
	params->color_value = &data->colors.gc;
	validate_and_parse_color(data, params);
	params->color_value = &data->colors.bc;
	params->is_last = 1;
	validate_and_parse_color(data, params);
}

static void	parse_floor_colors(t_data *data, t_color_init *params)
{
	params->color_value = &data->colors.rf;
	params->is_last = 0;
	validate_and_parse_color(data, params);
	params->color_value = &data->colors.gf;
	validate_and_parse_color(data, params);
	params->color_value = &data->colors.bf;
	params->is_last = 1;
	validate_and_parse_color(data, params);
}

void	init_colors(t_data *data, size_t rgb_lenght_f, size_t rgb_lenght_c)
{
	t_color_init	ceiling;
	t_color_init	floor;
	char			*s1;
	char			*s2;

	s1 = data->path_textures.c;
	s2 = data->path_textures.f;
	if (ft_strlen(s1) > 11 || ft_strlen(s2) > 11)
		exit_program(data, E_tex);
	ceiling.color_str = &s2;
	ceiling.rgb_length = &rgb_lenght_c;
	ceiling.orig_str = data->path_textures.c;
	floor.color_str = &s1;
	floor.rgb_length = &rgb_lenght_f;
	floor.orig_str = data->path_textures.f;
	parse_ceiling_colors(data, &ceiling);
	parse_floor_colors(data, &floor);
}
