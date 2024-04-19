/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:03:22 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/26 11:50:21 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	checkstate(char const *s1, char const *set, size_t *x)
{
	int	bbool;

	bbool = 0;
	while (set[x[1]] && bbool == 0)
	{
		while (set[x[1]] != 0 && set[x[1]++] == s1[x[0]] && bbool == 0)
		{
			x[5] = 1;
			if (x[3] == 0)
			{
				x[2]++;
				bbool = 1;
			}
		}
	}
}

static void	calc(char const *s1, char const *set, size_t *x)
{
	while (x[3] < 2)
	{
		x[1] = 0;
		x[5] = 0;
		checkstate(s1, set, x);
		if (x[5] == 0)
		{
			if (s1[x[0]] == 0)
				x[2] = 0;
			x[3]++;
		}
		x[0]++;
		if (x[3] == 1)
		{
			if (x[4] == 0)
			{
				x[3] = 2;
				x[5] = 2;
			}
			else
				x[0] = --x[4];
		}
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*pt;
	size_t	x[6];

	ft_bzero (&x, 4 * sizeof(size_t));
	if (s1 == 0)
		return (0);
	x[4] = ft_strlen(s1);
	if (x[4] == 0)
		return (ft_substr(s1, 0, 0));
	calc (s1, set, x);
	if (x[5] == 2)
	{
		pt = malloc(sizeof(char) * (0));
		pt[0] = 0;
		return (pt);
	}
	pt = ft_substr(s1, x[2], x[4] + 1 - x[2]);
	return (pt);
}
