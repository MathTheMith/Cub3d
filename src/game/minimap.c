/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:08:53 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 12:09:46 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	draw_square(t_data *data, t_square sq)
{
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	end_x = sq.x + sq.size;
	end_y = sq.y + sq.size;
	x = sq.x;
	while (x < end_x)
	{
		y = sq.y;
		while (y < end_y)
		{
			put_pixel(data, x, y, sq.color);
			y++;
		}
		x++;
	}
}

static int	get_cell_color(t_data *data, t_minimap *m, int dx, int dy)
{
	int	map_x;
	int	map_y;

	map_x = m->start_x + dx;
	map_y = m->start_y + dy;
	if (map_y >= 0 && map_y < data->map_size.height && map_x >= 0
		&& map_x < data->map_size.max_width)
	{
		if (data->char_map[map_y][map_x] == '1')
			return (0x000000);
		return (m->color_floor);
	}
	return (-1);
}

static void	draw_minimap_grid(t_data *data, t_minimap *m)
{
	int			dx;
	int			dy;
	int			color;
	t_square	sq;

	dx = 0;
	sq.size = m->cell_size;
	while (dx < m->grid_size)
	{
		dy = 0;
		while (dy < m->grid_size)
		{
			color = get_cell_color(data, m, dx, dy);
			if (color != -1)
			{
				sq.x = dx * m->cell_size;
				sq.y = dy * m->cell_size;
				sq.color = color;
				draw_square(data, sq);
			}
			dy++;
		}
		dx++;
	}
}

void	minimap(t_data *data)
{
	t_minimap	m;
	t_square	sq;

	m.view_distance = 10;
	m.grid_size = m.view_distance * 2;
	m.cell_size = (SCREEN_W / 5) / m.grid_size;
	m.start_x = (int)data->p.p_x - m.view_distance;
	m.start_y = (int)data->p.p_y - m.view_distance;
	m.color_floor = create_rgb(data->colors.RC, data->colors.GC,
			data->colors.BC);
	m.color_void = 0x000000;
	m.color_player = 0xFF0000;
	sq.x = 0;
	sq.y = 0;
	sq.size = m.cell_size * m.grid_size;
	sq.color = 0x000000;
	draw_square(data, sq);
	draw_minimap_grid(data, &m);
	sq.x = m.view_distance * m.cell_size;
	sq.y = m.view_distance * m.cell_size;
	sq.size = m.cell_size;
	sq.color = 0xFF0000;
	draw_square(data, sq);
}
