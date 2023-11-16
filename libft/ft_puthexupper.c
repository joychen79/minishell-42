/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:00:22 by jingchen          #+#    #+#             */
/*   Updated: 2023/06/10 15:25:21 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexupper(unsigned int n)
{
	static int	count;

	count = 0;
	if (n >= 16)
	{
		ft_puthexupper(n / 16);
		ft_putchar("0123456789ABCDEF"[n % 16]);
		count++;
	}
	else
	{
		ft_putchar("0123456789ABCDEF"[n % 16]);
		count++;
	}
	return (count);
}
