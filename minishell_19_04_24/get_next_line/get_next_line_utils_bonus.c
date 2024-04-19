/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:04:39 by rrimonte          #+#    #+#             */
/*   Updated: 2023/03/29 18:28:44 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc_get(size_t count, size_t size)
{
	void	*pt;
	size_t	i;

	i = 0;
	if (count != 0 && size != 0)
		pt = malloc(count * size);
	else
		pt = malloc(1);
	if (pt != 0)
	{
		while (i < (count * size))
		{
			((unsigned char *)pt)[i] = 0;
			i++;
		}
	}
	return (pt);
}

size_t	ft_strlcpy_get(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_size;

	i = 0;
	while (src[i] != '\0')
		i++;
	s_size = i;
	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && i < s_size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (s_size);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*pt;
	int		size;
	int		size2;
	int		i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	size = i;
	i = 0;
	while (s2[i] != '\0')
		i++;
	size2 = i + 1;
	pt = malloc((size + size2) * sizeof(char));
	if (pt != 0)
	{
		ft_strlcpy_get(pt, (char *)s1, size + 1);
		ft_strlcpy_get(pt + size, (char *)s2, size2);
	}
	free(s1);
	return (pt);
}

char	*ft_strchr_get(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (0);
}

t_list	*deletenod_get(t_list *buff)
{
	t_list	*temp;

	temp = buff->next;
	if (buff->next != 0)
		buff->next->previous = buff->previous;
	if (buff->previous != 0)
	{
		buff->previous->next = buff->next;
		temp = buff->previous;
	}
	free (buff);
	buff = temp;
	return (buff);
}
