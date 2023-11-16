/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:51:27 by jingchen          #+#    #+#             */
/*   Updated: 2023/06/10 15:24:22 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int n)
{
	static int	count;

	count = 0;
	if (n > 9)
	{
		ft_putunbr((n / 10));
		ft_putchar((n % 10) + '0');
		count++;
	}
	else
	{
		ft_putchar(n + '0');
		count = 1;
	}
	return (count);
}
