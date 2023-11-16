/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:00:22 by jingchen          #+#    #+#             */
/*   Updated: 2023/06/10 15:24:52 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long n)
{
	static int	count;

	count = 2;
	if (n >= 16)
	{
		ft_putptr(n / 16);
		ft_putchar("0123456789abcdef"[n % 16]);
		count++;
	}
	else
	{
		ft_putchar("0123456789abcdef"[n % 16]);
		count++;
	}
	return (count);
}
