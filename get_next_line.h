/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorosa <joaorosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 15:08:57 by joaorosa          #+#    #+#             */
/*   Updated: 2026/06/19 19:56:54 by joaorosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 42

void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *str);
int		find_newline(char *s);
char	*extract_line(char *remainder, int nl_pos);
void	shift_remainder(char *remainder, int nl_pos);
int		read_into_remainder(int fd, char *remainder);
char	*gnl(int fd);

#endif