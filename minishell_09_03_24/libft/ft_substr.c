/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:32:25 by rrimonte          #+#    #+#             */
/*   Updated: 2022/09/15 13:32:25 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mlen(unsigned int *start, size_t *len, size_t *s_len)
{
	if (*s_len < *start)
	{
		*start = 0;
		*len = 0;
	}
	else if (*s_len < *start + *len)
		*len = *s_len - *start;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*pt;
	size_t		i;
	size_t		s_len;
	size_t		z;

	if (s == 0)
		return (0);
	z = 0;
	s_len = ft_strlen(s);
	ft_mlen(&start, &len, &s_len);
	i = start;
	pt = malloc(sizeof(char) * (len + 1));
	if (pt == 0)
		return (0);
	while (s[i])
	{
		if (i < len + start)
		{
			pt[z] = s[i];
			z++;
		}
		i++;
	}
	pt[len] = '\0';
	return (pt);
}
