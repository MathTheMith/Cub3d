/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:51:29 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 14:37:40 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int parse_color_component(char **str, size_t *rgb_lenght, bool last)
{
    int value = 0;

    if (!ft_isdigit(**str))
        return (-1);
    while (**str && ft_isdigit(**str))
    {
        value = value * 10 + (**str - '0');
        (*str)++;
        *rgb_lenght+=1;
    }
    if (**str == ',' && last == 0)
    {
        (*str)++;
        *rgb_lenght+=1;
    }
    return (value);
}

void init_c_colors(t_data *data)
{
    char *s1 = data->path_textures.C;
    char *s2 = data->path_textures.F;

    char *orig_s1 = s1;
    char *orig_s2 = s2;
    size_t rgb_lenght_F;
    size_t rgb_lenght_C;
    
    rgb_lenght_F = 0;
    rgb_lenght_C = 0;

    data->colors.RC = parse_color_component(&s2, &rgb_lenght_C, 0);
    if (data->colors.RC < 0 || data->colors.RC >= 255)
        exit_program(data, E_tex);
    data->colors.GC = parse_color_component(&s2, &rgb_lenght_C, 0);
    if (data->colors.GC < 0 || data->colors.GC >= 255)
        exit_program(data, E_tex);
    data->colors.BC = parse_color_component(&s2, &rgb_lenght_C, 1);
    if (data->colors.BC < 0 || data->colors.BC >= 255)
        exit_program(data, E_tex);
    data->colors.RF = parse_color_component(&s1, &rgb_lenght_F, 0);
    if (data->colors.RF < 0 || data->colors.RF >= 255)
        exit_program(data, E_tex);
    data->colors.GF = parse_color_component(&s1, &rgb_lenght_F, 0);
    if (data->colors.GF < 0 || data->colors.GF >= 255)
        exit_program(data, E_tex);
    data->colors.BF = parse_color_component(&s1, &rgb_lenght_F, 1);
    if (data->colors.BF < 0 || data->colors.BF >= 255)
        exit_program(data, E_tex);

    // DEBUG
    // printf("\n rgblenghtF %zu, s1 %zu\n", rgb_lenght_F, ft_strlen(orig_s1));
    // printf("\n rgblenghtC %zu, s2 %zu\n", rgb_lenght_C, ft_strlen(orig_s2));
        
    if (ft_strlen(orig_s1) != rgb_lenght_F ||
        ft_strlen(orig_s2) != rgb_lenght_C)
        exit_program(data, E_tex);

}

