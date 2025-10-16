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
    
    y = 0;
    while (y < height / 2)
    {
        x = 0;
        while (x < width)
        {
            put_pixel(data, x, y, 0x87CEEB);
            x++;
        }
        y++;
    }
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            put_pixel(data, x, y, 0xD3D3D3 );
            x++;
        }
        y++;
    }
}

void draw_straight_line(t_data *data, int x0, int y0, int y1, int color)
{
    while (y0 < y1)
    {
        put_pixel(data, x0, y0, color);
        y0++;
    }
}