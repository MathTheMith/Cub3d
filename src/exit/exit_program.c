/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:01:15 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/19 10:49:58 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void destroy_mlx(t_data *data)
{
    int i;

    i = 0;
    while(i < 4)
    {
        if (data->teximg[i].img)
            mlx_destroy_image(data->mlx, data->teximg[i].img);
        i++;
    }
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
}


void exit_program(t_data *data, t_error error)
{
    if (error == No_error)
    {
        if (data)
            free_all(data);
        destroy_mlx(data);
        exit(EXIT_SUCCESS);
    }
    else 
    {
        print_error(error);
        if (data)
            free_all(data);
        destroy_mlx(data);
        exit(EXIT_FAILURE);
    }
}
