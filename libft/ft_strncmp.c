/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:15:25 by jingchen          #+#    #+#             */
/*   Updated: 2022/11/04 19:32:46 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && *s1 == *s2 && n > 0)
	{
			s1++;
			s2++;
			n--;
	}
	if (!n)
		return (0);
	return (*(unsigned char *)s1 - *((unsigned char *)s2));
}
