/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:35:13 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/26 10:29:19 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

static double	get_wall_x_position(t_ray *ray, t_player *p)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = p->p_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = p->p_x + ray->perp_wall_dist * ray->dir_x;
	return (wall_x - floor(wall_x));
}

static int	calculate_texture_x(t_ray *ray, t_teximg *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	setup_texture_mapping(t_wall_calc *calc, t_teximg *tex)
{
	int	offset;

	calc->step = 1.0 * tex->height / calc->line_height;
	offset = calc->draw_start - 500 + (calc->line_height >> 1);
	calc->tex_pos = offset * calc->step;
}

static void	render_wall_column(t_render_ctx *ctx, t_wall_calc *calc)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = calc->draw_start;
	while (y < calc->draw_end)
	{
		tex_y = (int)calc->tex_pos & (ctx->tex->height - 1);
		calc->tex_pos += calc->step;
		color = get_texel(ctx->tex, calc->tex_x, tex_y);
		if (ctx->ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(ctx->data, ctx->x, y, color);
		y++;
	}
}

void	draw_wall_line(t_data *data, t_ray *ray, t_player *p, int x)
{
	t_wall_calc		calc;
	t_render_ctx	ctx;

	calculate_wall_dimensions(&calc, ray);
	ctx.data = data;
	ctx.tex = get_wall_texture(data, ray);
	ctx.ray = ray;
	ctx.x = x;
	calc.wall_x = get_wall_x_position(ray, p);
	calc.tex_x = calculate_texture_x(ray, ctx.tex, calc.wall_x);
	setup_texture_mapping(&calc, ctx.tex);
	render_wall_column(&ctx, &calc);
}
