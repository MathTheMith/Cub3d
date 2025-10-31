/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:52:40 by tfournie          #+#    #+#             */
/*   Updated: 2025/10/31 13:29:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void parsing(int ac, char **av, t_data *data)
{
	int	len;
	int fd;
	
    data = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit_program(data, E_path);
	if (ac != 2)
		exit_program(data, E_nbarg);
	len = ft_strlen(av[1]);
	if (!((av[1][len - 1] == 'b') && (av[1][len - 2] == 'u') && (av[1][len
				- 3] == 'c') && (av[1][len - 4] == '.')))
		exit_program(data, E_ext);
}
