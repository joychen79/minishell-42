/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:56:30 by jingchen          #+#    #+#             */
/*   Updated: 2022/11/04 19:31:31 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strdup(const char *s1)
{
	size_t		i;
	size_t		j;
	char		*target;

	i = 0;
	while (s1[i] != '\0')
		i++;
	target = malloc(sizeof(char) * i + 1);
	if (target == 0)
		return (0);
	else
	{
		j = 0;
		while (s1[j] != '\0')
		{
			target[j] = s1[j];
		j++;
		}
	target[j] = '\0';
	}
	return (target);
}*/
char	*ft_strdup(const char *s1)
{
	char	*target;

	target = (char *)malloc(ft_strlen(s1) + 1);
	if (!target)
		return (0);
	else
		ft_strlcpy (target, s1, (ft_strlen(s1) + 1));
	return (target);
}
