/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:07:51 by tfournie          #+#    #+#             */
/*   Updated: 2025/10/16 11:51:01 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void free_all(t_data *data)
{
    int i;
    
    i = 0;
    if (data->map != NULL)
    {
        while(data->map[i])
        {
            if (data->map[i] != NULL)
            {
                free(data->map[i]);
                data->map[i] = NULL;
            }
            i++;
        }
        free(data->map);
        data->map = NULL;
    }
}
