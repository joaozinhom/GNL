#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

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
	char		buf[BUFFER_SIZE];
	ssize_t		bytes_read;
	int		nl_pos;
	size_t		rem_len;
	size_t		buf_len;
	char		*line;

	while (1)
	{
		nl_pos = find_newline(remainder);
		if (nl_pos >= 0)
		{
			line = extract_line(remainder, nl_pos);
			shift_remainder(remainder, nl_pos);
			return (line);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE - 1);
		if (bytes_read <= 0)
		{
			if (remainder[0] == '\0')
				return (NULL);
			line = malloc(ft_strlen(remainder) + 1);
			if (!line)
				return (NULL);
			ft_memcpy(line, remainder, ft_strlen(remainder) + 1);
			remainder[0] = '\0';
			return (line);
		}
		buf[bytes_read] = '\0';
		rem_len = ft_strlen(remainder);
		buf_len = ft_strlen(buf);
		ft_memcpy(remainder + rem_len, buf, buf_len + 1);
	}
}

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("foo.txt", 0);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	(line = gnl(fd));
	printf("%s", line);
	free(line);
	(line = gnl(fd));
	printf("%s", line);
	free(line);
	(line = gnl(fd));
	printf("%s", line);
	free(line);

	close(fd);
	return (0);
}