/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:46:24 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/22 00:34:19 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	matrix_count_limit(t_v_list	*v, char c)
{
	v->be = -1;
	v->be2 = -1;
	while (v->s2[v->x[0]])
	{
		if (v->s2[v->x[0]] == c
			&& v->s2[v->x[0] + 1] != c
			&& (v->be == 0 || v->be2 == 0
				|| (v->be == -1 && v->be2 == -1)))
			v->x[2]++;
		v->x[0]++;
	}
}

void	limit(t_v_list	*v, int bol)
{
	if (bol == 0)
	{
		v->be = 0;
		v->aux2--;
	}
	else if (bol == 1)
	{
		v->be2 = 0;
		v->aux--;
	}
	else if (bol == 2)
	{
		v->be = 1;
		if (v->aux2 != 1)
			v->x[2]--;
		v->aux2--;
	}
	else if (bol == 3)
	{
		v->be2 = 1;
		if (v->aux != 1)
			v->x[2]--;
		v->aux--;
	}
}

char	**str_count_limit(t_v_list	*v, char c, char **pt)
{
	if ((v->s2[v->x[0]] == c && v->s2[v->x[0] + 1] != c && (v->be == 0
				|| v->be2 == 0 || (v->be == -1 && v->be2 == -1))))
	{
		pt[v->x[1]] = (char *)malloc((v->x[2] + 1) * sizeof(char));
		if (pt == 0)
		{
			ft_free_limit(pt);
			return (0);
		}
		v->x[1]++;
		v->x[2] = 0;
	}
	else if (v->s2[v->x[0]] != c || v->be == 1 || v->be2 == 1)
	{
		v->x[2]++;
	}
	return (pt);
}

char	**ft_aux_limit(t_v_list	*v, char c, char **pt)
{
	while (v->s2[v->x[0]])
	{
		v->x[0]++;
	}
	v->x[0] = 0;
	pt = asg_limit(v, c);
	if (pt != 0)
	{
		v->x[0] = 0;
		v->x[1] = 0;
		v->x[2] = 0;
		pt = f_writ_limit(v, pt, c);
	}
	free(v->s2);
	free(v);
	return (pt);
}

char	**str_write_limit(t_v_list	*v, char **pt, int bol)
{
	if (bol == 0)
	{
		v->be = -1;
		v->be2 = -1;
	}
	if (bol == 1)
	{
		pt[v->x[1]][v->x[2]] = v->s2[v->x[0]];
		v->x[2] = v->x[2] + 1;
	}
	return (pt);
}
