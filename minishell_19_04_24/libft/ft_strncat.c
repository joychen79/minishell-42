/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:20:36 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/26 11:50:14 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_calc(size_t *max, size_t i, char *dest, const char *src)
{
	while (dest && dest[i])
		i++;
	max[0] = i;
	i = 0;
	while (src[i])
		i++;
	max[1] = i;
	i = 0;
}

size_t	ft_strncat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	max[2];
	size_t	aux;

	i = 0;
	ft_calc(max, i, dst, src);
	if (dstsize > max[0])
	{
		dstsize = dstsize - max[0];
		while (src && src[i] && i != dstsize && dstsize > 0)
		{
			dst[max[0]++] = src[i];
			i++;
		}
		aux = i;
		dst[max[0]] = 0;
		return (max[0] + max[1] - aux);
	}
	else
		return (max[1] + dstsize);
}
