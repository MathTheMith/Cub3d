/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:25:03 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:45:33 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_texel(t_teximg *tex, int x, int y)
{
	char	*addr;

	addr = (char *)tex->px + (y * tex->line_len) + (x * (tex->bpp / 8));
	return (*(unsigned int *)addr);
}

void	calculate_wall_dimensions(t_wall_calc *calc, t_ray *ray)
{
	calc->line_height = (int)(1000 / ray->perp_wall_dist);
	calc->draw_start = -calc->line_height / 2 + 500;
	calc->draw_end = calc->line_height / 2 + 500;
	if (calc->draw_start < 0)
		calc->draw_start = 0;
	if (calc->draw_end >= 1000)
		calc->draw_end = 999;
}

t_teximg	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&data->teximg[2]);
		else
			return (&data->teximg[3]);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&data->teximg[0]);
		else
			return (&data->teximg[1]);
	}
}
