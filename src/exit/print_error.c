/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:09:06 by tfournie          #+#    #+#             */
/*   Updated: 2025/11/18 19:11:01 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_error(t_error error)
{
    if (error == E_path)
        printf("Error_type: path failed\nThe path of the map doesn't exist!\n");
    if (error == E_malloc)
        printf("Error_type: malloc failed\nIssue with an allocation!\n");
    if (error == E_nbarg)
        printf("Error_type: numbers of arguments\nYou just need to put the path of the map!\n");
    if (error == E_ext)
        printf("Error_type: bad extension\nYou need a map with .cub at the end!\n");
    else if (error == E_map)
        printf("Error\nType : E_map\nThe map isn't valid\n");
}