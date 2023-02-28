/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hman <hman@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 16:36:42 by hakaman       #+#    #+#                 */
/*   Updated: 2021/06/22 16:57:12 by hman          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s != '\0')
	{
		s++;
		counter++;
	}
	return (counter);
}

char	*gnl_strchr(const char *s, int c)
{
	const char		*p;
	unsigned char	e;
	int				done;

	p = s;
	e = (unsigned char)c;
	done = 0;
	while (!done)
	{
		if (*p == e)
			return ((char *)p);
		else if (*p == '\0' && e != '\0')
			done = 1;
		p++;
	}
	return (NULL);
}

static void	appending(char **dest, const char *src)
{
	while (*src != '\0')
	{
		**dest = *src;
		(*dest)++;
		src++;
	}
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_lenght;
	char	*joinedstr;
	char	*joinedstr_p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_length = gnl_strlen(s1);
	s2_lenght = gnl_strlen(s2);
	joinedstr = malloc(s1_length + s2_lenght + 1);
	if (joinedstr == NULL)
		return (NULL);
	joinedstr_p = joinedstr;
	appending(&joinedstr_p, s1);
	appending(&joinedstr_p, s2);
	*joinedstr_p = '\0';
	return (joinedstr);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	src_length = gnl_strlen(src);
	if (size == 0)
		return (src_length);
	else
	{
		i = 0;
		while (src[i] != '\0' && (i < (size - 1)))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_length);
}
