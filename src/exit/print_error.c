/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:03:15 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/27 10:06:17 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	print_error_next(t_error error);

void	print_error(t_error error)
{
	if (error == E_path)
		printf("Error\nType: E_path\nThe path of the map doesn't exist!\n");
	else if (error == E_malloc)
		printf("Error\nType: E_malloc\nIssue with an allocation!\n");
	else if (error == E_nbarg)
	{
		printf("Error\nType: E_nbarg\n");
		printf("You just need to put the path of the map!\n");
	}
	else if (error == E_ext)
		printf("Error\nType: E_ext\nYou need a map with .cub at the end!\n");
	else if (error == E_mlx_env)
		printf("Error\nType: E_mlx_env\nYou need the env!\n");
	else if (error == E_mlx_win)
		printf("Error\nType: E_mlx_win\nCreation of the window fail!\n");
	else if (error == E_tex)
	{
		printf("Error\nType: E_tex\nThe textures");
		printf(" of the wall is invalid(check the file or the path)!\n");
	}
	else if (error == E_map)
		printf("Error\nType: E_map\nThe map isn't valid!\n");
	else
		print_error_next(error);
}

static void	print_error_next(t_error error)
{
	if (error == E_read)
		printf("Error\nType: E_read\nCannot read the document!\n");
	else if (error == E_color)
		printf("Error\nType: E_color\nWrong number for the color of F or C!\n");
	else if (error == E_maps)
		printf("Error\nType: E_maps\nCouldn't find the map!\n");
	else if (error == E_mapc)
		printf("Error\nType: E_maps\nWrong character in the doc!\n");
}
