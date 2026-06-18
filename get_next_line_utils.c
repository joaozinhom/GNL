# include <unistd.h>
# include <stdlib.h>
//#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == NULL)
	{
		return (str);
	}
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s = s + 1;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen((char *)src);
	if (len + 1 < size)
		dest = ft_memcpy(dest, src, len + 1);
	else if (size != 0)
	{
		dest = ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (len);
}
