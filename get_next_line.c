/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorosa <joaorosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:08:50 by joaorosa          #+#    #+#             */
/*   Updated: 2026/06/19 19:56:30 by joaorosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line(char *remainder, int nl_pos)
{
	char	*line;

	line = malloc(nl_pos + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, remainder, nl_pos + 1);
	line[nl_pos + 1] = '\0';
	return (line);
}

void	shift_remainder(char *remainder, int nl_pos)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(remainder);
	i = 0;
	while (nl_pos + 1 + i < len)
	{
		remainder[i] = remainder[nl_pos + 1 + i];
		i++;
	}
	remainder[i] = '\0';
}

char	*gnl(int fd)
{
	static char	remainder[BUFFER_SIZE * 2];
	int			nl_pos;
	char		*line;

	if (read_into_remainder(fd, remainder) == 0 && remainder[0] == '\0')
		return (NULL);
	nl_pos = find_newline(remainder);
	if (nl_pos >= 0)
	{
		line = extract_line(remainder, nl_pos);
		shift_remainder(remainder, nl_pos);
		return (line);
	}
	line = malloc(ft_strlen(remainder) + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, remainder, ft_strlen(remainder) + 1);
	remainder[0] = '\0';
	return (line);
}
