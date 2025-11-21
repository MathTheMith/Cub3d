/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:30:00 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 20:00:00 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/****************************** UTILS TEXEL ******************************/

unsigned int    get_texel(t_teximg *tex, int x, int y)
{
    char *addr = (char *)tex->px
        + (y * tex->line_len)
        + (x * (tex->bpp / 8));
    return (*(unsigned int *)addr);
}

/****************************** RAY INIT ********************************/

void init_ray_direction(t_ray *ray, t_player *p, int x)
{
    ray->camera_x = 2 * x / (double)SCREEN_W - 1;
    ray->dir_x = p->dir_x + p->plane_x * ray->camera_x;
    ray->dir_y = p->dir_y + p->plane_y * ray->camera_x;

    ray->map_x = (int)p->p_x;
    ray->map_y = (int)p->p_y;
}

void init_ray_delta(t_ray *ray)
{
    double inv_dx = 1.0 / fabs(ray->dir_x);
    double inv_dy = 1.0 / fabs(ray->dir_y);

    ray->delta_dist_x = inv_dx;
    ray->delta_dist_y = inv_dy;
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

/****************************** DDA **************************************/

void perform_dda(t_ray *ray, t_data *data)
{
    int hit = 0;

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
        ray->perp_wall_dist = (ray->map_x - p->p_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - p->p_y + (1 - ray->step_y) / 2) / ray->dir_y;
}

/****************************** TEXTURE CHOICE ***************************/

t_teximg *get_wall_texture(t_data *data, t_ray *ray)
{
    if (ray->side == 0) // vertical hit
    {
        if (ray->dir_x > 0)
            return (&data->teximg[2]); // WE
        else
            return (&data->teximg[3]); // EA
    }
    else // horizontal hit
    {
        if (ray->dir_y > 0)
            return (&data->teximg[0]); // NO
        else
            return (&data->teximg[1]); // SO
    }
}

/****************************** DRAW WALL ********************************/

void draw_wall_line(t_data *data, t_ray *ray, t_player *p, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    t_teximg *tex;
    int tex_x;

    line_height = (int)(SCREEN_H / ray->perp_wall_dist);
    draw_start = -line_height / 2 + SCREEN_H / 2;
    draw_end = line_height / 2 + SCREEN_H / 2;
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= SCREEN_H)
        draw_end = SCREEN_H - 1;
    tex = get_wall_texture(data, ray);

    // ----- Compute exact hit point -----
    double wall_x;

    if (ray->side == 0)
        wall_x = p->p_y + ray->perp_wall_dist * ray->dir_y;
    else
        wall_x = p->p_x + ray->perp_wall_dist * ray->dir_x;
    wall_x -= floor(wall_x);
    tex_x = (int)(wall_x * (double)tex->width);
    if (ray->side == 0 && ray->dir_x < 0) 
        tex_x = tex->width - tex_x - 1;
    if (ray->side == 1 && ray->dir_y > 0) 
        tex_x = tex->width - tex_x - 1;

    // ----- Vertical texture stepping -----
    double step = 1.0 * tex->height / line_height;
    int offset = draw_start - (SCREEN_H >> 1) + (line_height >> 1);
    double tex_pos = offset * step;

    // if (x % 100000 == 0)
    // {   
    //     printf("=====DEBUG======\n");
    //     printf("taille mur     :%d\n", line_height);
    //     printf("draw_start:%d\n", draw_start);
    //     printf("draw_end     :%d\n", draw_end);
    //     printf("side:%d\n", ray->side);
    //     printf("wall_x:%.4f\n", wall_x);
    //     printf("tex_x:%d\n", tex_x);
    //     printf("step:%.2f\n", step);
    //     printf("offset:%d\n", offset);
    //     printf("tex_pos:%.2f\n", tex_pos);
    //     printf("==============\n\n");
    // }

    int y;
    int tex_y;
    unsigned int color;

    y = draw_start;
    while (y < draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_texel(tex, tex_x, tex_y);
        if (ray->side == 1)
            color = (color >> 1) & 0x7F7F7F;
        put_pixel(data, x, y, color);
        y++;
    }
}

/****************************** MAIN RAYCAST *****************************/

void draw_wall(t_data *data, t_player *p)
{
    int x = 0;
    t_ray ray;

    while (x < SCREEN_W)
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
