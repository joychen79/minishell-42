/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:53:48 by jingchen          #+#    #+#             */
/*   Updated: 2022/10/11 18:14:00 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int nb)
{
	int	count;

	count = 0;
	if (nb <= 0)
		count++;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nb;
	int			len;

	nb = n;
	len = ft_count(nb);
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nb == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len--] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		str[0] = '-';
	}
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
