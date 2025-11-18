/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:25:21 by marvin            #+#    #+#             */
/*   Updated: 2025/10/15 23:25:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void move_forward(t_data *data)
{
    double newX;
    double newY;

    newX = data->p.p_x + data->p.dir_x * 0.1;
    newY = data->p.p_y + data->p.dir_y * 0.1;
    
    if (data->map[(int)newY][(int)newX] == 0)
    {
        data->p.p_x = newX;
        data->p.p_y = newY;
    }
}

void move_backward(t_data *data)
{
    double newX;
    double newY;

    newX = data->p.p_x - data->p.dir_x * 0.1;
    newY = data->p.p_y - data->p.dir_y * 0.1;
    
    if (data->map[(int)newY][(int)newX] == 0)
    {
        data->p.p_x = newX;
        data->p.p_y = newY;
    }
}

void move_left(t_data *data)
{
    double newX;
    double newY;

    newX = data->p.p_x + data->p.dir_y * 0.1;
    newY = data->p.p_y - data->p.dir_x * 0.1;
    
    if (data->map[(int)newY][(int)newX] == 0)
    {
        data->p.p_x = newX;
        data->p.p_y = newY;
    }
}

void move_right(t_data *data)
{
    double newX;
    double newY;

    newX = data->p.p_x - data->p.dir_y * 0.1;
    newY = data->p.p_y + data->p.dir_x * 0.1;
    
    if (data->map[(int)newY][(int)newX] == 0)
    {
        data->p.p_x = newX;
        data->p.p_y = newY;
    }
}

void rotate_direction(t_player *p, double rotSpeed)
{
    double oldDirX;

    oldDirX = p->dir_x;
    p->dir_x = p->dir_x * cos(rotSpeed) - p->dir_y * sin(rotSpeed);
    p->dir_y = oldDirX * sin(rotSpeed) + p->dir_y * cos(rotSpeed);
}

void rotate_plane(t_player *p, double rotSpeed)
{
    double oldPlaneX;

    oldPlaneX = p->plane_x;
    p->plane_x = p->plane_x * cos(rotSpeed) - p->plane_y * sin(rotSpeed);
    p->plane_y = oldPlaneX * sin(rotSpeed) + p->plane_y * cos(rotSpeed);
}

void rotate_left(t_data *data)
{
    double rotSpeed;

    rotSpeed = 0.07;
    rotate_direction(&data->p, -rotSpeed);
    rotate_plane(&data->p, -rotSpeed);
}

void rotate_right(t_data *data)
{
    double rotSpeed;

    rotSpeed = 0.07;
    rotate_direction(&data->p, rotSpeed);
    rotate_plane(&data->p, rotSpeed);
}