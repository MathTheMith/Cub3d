/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:51:29 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/24 12:08:32 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int parse_color_component(const char **str)
{
    int value = 0;

    while (**str && ft_isdigit(**str))
    {
        value = value * 10 + (**str - '0');
        (*str)++;
    }
    if (**str == ',')
        (*str)++;
    return value;
}

void init_c_colors(t_data *data)
{
    const char *s1 = data->path_textures.C;
    const char *s2 = data->path_textures.F;

    data->colors.RC = parse_color_component(&s2);
    if (!data->colors.RC || data->colors.RC >= 255)
        exit_program(data, E_tex);
    data->colors.GC = parse_color_component(&s2);
    if (!data->colors.GC || data->colors.GC >= 255)
        exit_program(data, E_tex);
    data->colors.BC = parse_color_component(&s2);
    if (!data->colors.BC || data->colors.BC >= 255)
        exit_program(data, E_tex);
    data->colors.RF = parse_color_component(&s1);
    if (!data->colors.RF || data->colors.RF >= 255)
        exit_program(data, E_tex);
    data->colors.GF = parse_color_component(&s1);
    if (!data->colors.GF || data->colors.GF >= 255)
        exit_program(data, E_tex);
    data->colors.BF = parse_color_component(&s1);
    if (!data->colors.BF || data->colors.BF >= 255)
        exit_program(data, E_tex);
    // DEBUG
    // static int q = 0;
    // if (q == 0)
    //     printf("prout:%d, %d, %d\n",
    //            data->colors.RF, data->colors.GF, data->colors.BF);
    // q++;
}

