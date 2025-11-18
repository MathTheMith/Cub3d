/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:04:08 by marvin            #+#    #+#             */
/*   Updated: 2025/10/15 16:04:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int create_rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;
    
    if (x < 0 || x >= 1500 || y < 0 || y >= 1000)
        return;
    dst = data->data + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_background(t_data *data, int width, int height)
{
    int x;
    int y;
    int color_f = create_rgb(data->colors.RF, data->colors.GF, data->colors.BF);
    int color_c = create_rgb(data->colors.RC, data->colors.GC, data->colors.BC);

    y = 0;
    while (y < height / 2)
    {
        x = -1;
        while (++x < width)
            put_pixel(data, x, y, color_f);
        y++;
    }
    while (y < height)
    {
        x = -1;
        while (++x < width)
            put_pixel(data, x, y, color_c);
        y++;
    }
}


void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    
    if (x0 < x1)
        sx = 1;
    else
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    
    err = dx - dy;
    while (1)
    {
        put_pixel(data, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
