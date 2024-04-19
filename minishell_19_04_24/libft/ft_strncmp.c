/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:40:52 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/24 20:36:58 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*sx;
	unsigned char	*sy;

	sx = (unsigned char *)s1;
	sy = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((sx[i] == sy[i]) && (sx[i] != '\0' || sy[i] != '\0') && i < n - 1)
		i++;
	if (sx[i] == '\0' && sy[i] == '\n')
		return (0);
	return (sx[i] - sy[i]);
}
