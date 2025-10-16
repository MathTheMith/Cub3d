/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:30:00 by marvin            #+#    #+#             */
/*   Updated: 2025/10/15 16:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_ray_direction(t_ray *ray, t_player *p, int x)
{
    ray->camera_x = 2 * x / (double)1500 - 1;
    ray->dir_x = p->dir_x + p->plane_x * ray->camera_x;
    ray->dir_y = p->dir_y + p->plane_y * ray->camera_x;
    ray->map_x = (int)p->p_x;
    ray->map_y = (int)p->p_y;
}

void init_ray_delta(t_ray *ray)
{
    ray->delta_dist_x = fabs(1.0 / ray->dir_x);
    ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

void init_ray_step(t_ray *ray, t_player *p)
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

void perform_dda(t_ray *ray, t_data *data)
{
    int hit;

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

void calculate_wall_distance(t_ray *ray, t_player *p)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - p->p_x 
            + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - p->p_y 
            + (1 - ray->step_y) / 2) / ray->dir_y;
}

void draw_wall_line(t_data *data, t_ray *ray, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    int color;

    line_height = (int)(1000 / ray->perp_wall_dist);
    
    draw_start = -line_height / 2 + 1000 / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + 1000 / 2;
    if (draw_end >= 1000)
        draw_end = 1000 - 1;
    
    color = 0xFF0000;
    if (ray->side == 1)
        color = 0x880000;
    draw_straight_line(data, x, draw_start, draw_end, color);
}

void draw_wall(t_data *data, t_player *p)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < 1500)
    {
        init_ray_direction(&ray, p, x);
        init_ray_delta(&ray);
        init_ray_step(&ray, p);
        perform_dda(&ray, data);
        calculate_wall_distance(&ray, p);
        draw_wall_line(data, &ray, x);
        x++;
    }
    
}