/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_limit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:19:52 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/24 10:36:45 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_limit(char **pt)
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

char	**checkmalloc_limit(t_v_list	*v, char c, char **pt)
{
	v->be = -1;
	v->be2 = -1;
	v->aux = v->x[3];
	v->aux2 = v->x[4];
	while (v->s2[v->x[0]])
	{
		pt = str_count_limit(v, c, pt);
		v->x[0]++;
		if (v->s2[v->x[0]] == '\0')
			pt[v->x[1]] = (char *)malloc((v->x[2] + 1) * sizeof(char));
		if (pt == 0)
		{
			ft_free_limit(pt);
			return (0);
		}
	}
	return (pt);
}

char	**f_writ_limit(t_v_list	*v, char **pt, char c)
{
	str_write_limit(v, pt, 0);
	while (v->s2[v->x[0]])
	{
		if (v->be2 == 1 && v->s2[v->x[0]] == 34)
			limit(v, 1);
		else if (v->be == 1 && v->s2[v->x[0]] == 39)
			limit(v, 0);
		else if ((v->s2[v->x[0]] == c && v->s2[v->x[0] + 1] != c && (v->be == 0
					|| v->be2 == 0 || (v->be == -1 && v->be2 == -1))))
		{
			pt[v->x[1]][v->x[2]] = '\0';
			v->x[1] = v->x[1] + 1;
			v->x[2] = 0;
		}
		else if (v->s2[v->x[0]] != c || v->be == 1 || v->be2 == 1)
			str_write_limit(v, pt, 1);
		v->x[0]++;
		if (v->s2[v->x[0]] == '\0')
		{
			pt[v->x[1]][v->x[2]] = '\0';
			v->x[1] = v->x[1] + 1;
		}
	}
	pt[v->x[1]] = 0;
	return (pt);
}

char	**asg_limit(t_v_list	*v, char c)
{
	char	**pt;

	if (v->s2 == 0)
		return (0);
	matrix_count_limit(v, c);
	v->x[0] = 0;
	pt = (char **) malloc ((v->x[2] + 1) * sizeof(char *));
	if (pt == 0)
		return (pt);
	v->x[2] = 0;
	pt = checkmalloc_limit(v, c, pt);
	if (pt == 0)
	{
		ft_free_limit(pt);
		return (0);
	}
	return (pt);
}

char	**ft_split_limit(char const *s, char c)
{
	t_v_list	*v;
	char		**pt;

	pt = 0;
	v = malloc(sizeof(*v));
	if (v == NULL)
		return (0);
	ft_bzero (v->x, 3 * sizeof(size_t));
	v->x[2] = 1;
	v->x[3] = 0;
	v->x[4] = 0;
	v->ac[0] = c;
	v->ac[1] = '\0';
	v->s2 = ft_strtrim(s, v->ac);
	if (v->s2 == 0)
	{
		free(v->s2);
		return (0);
	}
	pt = ft_aux_limit(v, c, pt);
	return (pt);
}
