/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:40:02 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/26 10:29:19 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	init_ray_direction(t_ray *ray, t_player *p, int x)
{
	ray->camera_x = 2 * x / (double)1500 - 1;
	ray->dir_x = p->dir_x + p->plane_x * ray->camera_x;
	ray->dir_y = p->dir_y + p->plane_y * ray->camera_x;
	ray->map_x = (int)p->p_x;
	ray->map_y = (int)p->p_y;
}

void	init_ray_delta(t_ray *ray)
{
	double	inv_dx;
	double	inv_dy;

	inv_dx = 1.0 / fabs(ray->dir_x);
	inv_dy = 1.0 / fabs(ray->dir_y);
	ray->delta_dist_x = inv_dx;
	ray->delta_dist_y = inv_dy;
}

void	init_ray_step(t_ray *ray, t_player *p)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->p_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->p_y) * ray->delta_dist_y;
	}
}
