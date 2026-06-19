/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorosa <joaorosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:09:02 by joaorosa          #+#    #+#             */
/*   Updated: 2026/06/19 19:56:44 by joaorosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (dst);
	s = (const char *)src;
	d = (char *)dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	read_into_remainder(int fd, char *remainder)
{
	char	buf[BUFFER_SIZE];
	ssize_t	bytes_read;

	while (find_newline(remainder) < 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
			return (bytes_read);
		buf[bytes_read] = '\0';
		ft_memcpy(remainder + ft_strlen(remainder), buf, ft_strlen(buf) + 1);
	}
	return (1);
}
