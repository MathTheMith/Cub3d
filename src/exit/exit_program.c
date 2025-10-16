/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:01:15 by tfournie          #+#    #+#             */
/*   Updated: 2025/10/16 11:57:04 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void exit_program(t_data *data, t_error error)
{
    if (error == No_error)
    {
        if (data)
            free_all(data);
        exit(EXIT_SUCCESS);
    }
    else 
    {
        print_error(error);
        if (data)
            free_all(data);
        exit(EXIT_FAILURE);
    }
}
