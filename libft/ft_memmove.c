/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:47:13 by jingchen          #+#    #+#             */
/*   Updated: 2022/11/04 19:30:36 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void*src, size_t len)
{
	char	*dest;
	char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len--)
		{
			*(dest + len) = *(source + len);
		}
		return (dst);
	}
	while (len--)
		*(dest++) = *(source++);
	return (dst);
}
