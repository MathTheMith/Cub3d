/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:29:47 by tomm              #+#    #+#             */
/*   Updated: 2025/11/26 10:28:59 by mvachon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	if (!s || !f)
		return (NULL);
	i = -1;
	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = f(i, s[i]);
	dest[i] = '\0';
	return (dest);
}
