/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:52:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/10/16 11:56:34 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void parsing(int ac, char **av, t_data *data)
{
	int	len;

    data = NULL;
	if (ac != 2)
		exit_program(data, E_nbarg);
	len = ft_strlen(av[1]);
	if (!((av[1][len - 1] == 'b') && (av[1][len - 2] == 'u') && (av[1][len
				- 3] == 'c') && (av[1][len - 4] == '.')))
		exit_program(data, E_ext);
}
