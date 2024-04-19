/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:19:52 by rrimonte          #+#    #+#             */
/*   Updated: 2023/09/06 18:33:26 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **pt)
{
	int	i;

	i = 0;
	while (pt[i])
	{
		free(pt[i]);
		i++;
	}
	free(pt);
}

static char	**checkmalloc(char *s2, size_t *x, char c, char **pt)
{
	while (s2[x[0]])
	{
		if ((s2[x[0]] == c && s2[x[0] + 1] != c))
		{
			pt[x[1]] = (char *)malloc((x[2] + 1) * sizeof(char));
			if (pt == 0)
			{
				ft_free(pt);
				return (0);
			}
			x[1]++;
			x[2] = 0;
		}
		else if (s2[x[0]] != c)
			x[2]++;
		x[0]++;
		if (s2[x[0]] == '\0')
			pt[x[1]] = (char *)malloc((x[2] + 1) * sizeof(char));
		if (pt == 0)
		{
			ft_free(pt);
			return (0);
		}
	}
	return (pt);
}

static char	**f_writ(char *s2, char **pt, size_t *x, char c)
{
	while (s2[x[0]])
	{
		if ((s2[x[0]] == c && s2[x[0] + 1] != c))
		{
			pt[x[1]][x[2]] = '\0';
			x[1] = x[1] + 1;
			x[2] = 0;
		}
		else if (s2[x[0]] != c)
		{
			pt[x[1]][x[2]] = s2[x[0]];
			x[2] = x[2] + 1;
		}
		x[0]++;
		if (s2[x[0]] == '\0')
		{
			pt[x[1]][x[2]] = '\0';
			x[1] = x[1] + 1;
		}
	}
	pt[x[1]] = 0;
	return (pt);
}

static char	**asg(char *s2, size_t *x, char c)
{
	char	**pt;

	if (s2 == 0)
		return (0);
	while (s2[x[0]])
	{
		if (s2[x[0]] == c && s2[x[0] + 1] != c)
			x[2]++;
		x[0]++;
	}
	x[0] = 0;
	pt = (char **) malloc ((x[2] + 1) * sizeof(char *));
	if (pt == 0)
		return (pt);
	x[2] = 0;
	pt = checkmalloc(s2, x, c, pt);
	if (pt == 0)
	{
		ft_free(pt);
		return (0);
	}
	return (pt);
}

char	**ft_split(char const *s, char c)
{
	char	**pt;
	char	*s2;
	char	ac[2];
	size_t	x[3];

	ft_bzero (&x, 3 * sizeof(size_t));
	x[2] = 1;
	ac[0] = ' ';
	ac[1] = '\0';
	s2 = ft_strtrim(s, ac);
	if (s2 == 0)
	{
		free(s2);
		return (0);
	}
	pt = asg(s2, x, c);
	if (pt != 0)
	{
		x[0] = 0;
		x[1] = 0;
		x[2] = 0;
		pt = f_writ(s2, pt, x, c);
	}
	free(s2);
	return (pt);
}
