/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:10:28 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 17:40:20 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1500 || y < 0 || y >= 1000)
		return ;
	dst = data->data + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	fill_line(t_data *data, int y, int width, int color)
{
	int				x;
	unsigned int	*row;

	x = 0;
	row = (unsigned int *)(data->data + y * data->line_len);
	while (x < width)
	{
		row[x] = color;
		x++;
	}
}

void	draw_background(t_data *data, int width, int height)
{
	int	color_floor;
	int	color_ceiling;
	int	y_start;
	int	y_end;

	y_start = 0;
	y_end = height / 2;
	color_floor = create_rgb(data->colors.rf, data->colors.gf, data->colors.bf);
	color_ceiling = create_rgb(data->colors.rc, data->colors.gc,
			data->colors.bc);
	while (y_start < y_end)
	{
		fill_line(data, y_start, width, color_floor);
		y_start++;
	}
	y_start = height / 2;
	y_end = height;
	while (y_start < y_end)
	{
		fill_line(data, y_start, width, color_ceiling);
		y_start++;
	}
}
