/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:58:25 by mvachon           #+#    #+#             */
/*   Updated: 2025/11/17 14:58:25 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void set_player_north(t_data *data, int i, int j)
{
    data->p.p_x = j + 0.5;
    data->p.p_y = i + 0.5;
    data->p.dir_x = 0;
    data->p.dir_y = -1;
    data->p.plane_x = 0.75;
    data->p.plane_y = 0;
}

void set_player_south(t_data *data, int i, int j)
{
    data->p.p_x = j + 0.5;
    data->p.p_y = i + 0.5;
    data->p.dir_x = 0;
    data->p.dir_y = 1;
    data->p.plane_x = -0.75;
    data->p.plane_y = 0;
}

void set_player_east(t_data *data, int i, int j)
{
    data->p.p_x = j + 0.5;
    data->p.p_y = i + 0.5;
    data->p.dir_x = 1;
    data->p.dir_y = 0;
    data->p.plane_x = 0;
    data->p.plane_y = 0.75;
}

void set_player_west(t_data *data, int i, int j)
{
    data->p.p_x = j + 0.5;
    data->p.p_y = i + 0.5;
    data->p.dir_x = -1;
    data->p.dir_y = 0;
    data->p.plane_x = 0;
    data->p.plane_y = -0.75;
}
