/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:58:50 by rrimonte          #+#    #+#             */
/*   Updated: 2023/10/16 12:49:36 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_size;

	i = 0;
	s_size = ft_strlen(src);
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
