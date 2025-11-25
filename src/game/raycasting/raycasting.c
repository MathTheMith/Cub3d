/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:44:17 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/25 15:48:41 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	perform_dda(t_ray *ray, t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == 1)
			hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray, t_player *p)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - p->p_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - p->p_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
}

void	draw_wall(t_data *data, t_player *p)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < 1500)
	{
		init_ray_direction(&ray, p, x);
		init_ray_delta(&ray);
		init_ray_step(&ray, p);
		perform_dda(&ray, data);
		calculate_wall_distance(&ray, p);
		draw_wall_line(data, &ray, p, x);
		x++;
	}
}
