/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:51:29 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/17 18:10:25 by tfournie         ###   ########.fr       */
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
    const char *s1 = data->textures.C;
    const char *s2 = data->textures.F;

    data->colors.RC = parse_color_component(&s2);
    data->colors.GC = parse_color_component(&s2);
    data->colors.BC = parse_color_component(&s2);
    data->colors.RF = parse_color_component(&s1);
    data->colors.GF = parse_color_component(&s1);
    data->colors.BF = parse_color_component(&s1);

    // DEBUG
    static int q = 0;
    if (q == 0)
        printf("prout:%d, %d, %d\n",
               data->colors.RF, data->colors.GF, data->colors.BF);
    q++;
}

