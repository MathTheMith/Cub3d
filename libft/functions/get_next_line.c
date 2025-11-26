/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfournie <tfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:59:09 by math              #+#    #+#             */
/*   Updated: 2025/11/26 10:19:22 by tfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static void	*ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*extract_line(char **buffer, ssize_t bytes_read)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	if (!*buffer || !**buffer)
		return (NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	if (!line)
		return (NULL);
	temp = ft_strdup(*buffer + i + ((*buffer)[i] == '\n'));
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	ft_free(buffer);
	*buffer = temp;
	if (bytes_read == 0)
		ft_free(buffer);
	return (line);
}

static char	*read_and_store(int fd, char *buffer, ssize_t *bytes_read)
{
	char	temp[42 + 1];
	char	*joined;

	while (!ft_strchr_gnl(buffer, '\n'))
	{
		*bytes_read = read(fd, temp, 42);
		if (*bytes_read < 0)
		{
			ft_free(&buffer);
			return (NULL);
		}
		if (*bytes_read <= 0)
			break ;
		temp[*bytes_read] = '\0';
		joined = ft_strjoin(buffer, temp);
		if (!joined)
		{
			ft_free(&buffer);
			return (NULL);
		}
		ft_free(&buffer);
		buffer = joined;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	ssize_t		bytes_read;
	char		*str;

	bytes_read = 42;
	if (fd < 0)
		return (ft_free(&buffer));
	buffer = read_and_store(fd, buffer, &bytes_read);
	if (!buffer || (!*buffer && bytes_read == 0))
	{
		ft_free(&buffer);
		return (NULL);
	}
	str = extract_line(&buffer, bytes_read);
	if (!str)
	{
		ft_free(&buffer);
		return (NULL);
	}
	return (str);
}
