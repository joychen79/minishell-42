/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:21:35 by jingchen          #+#    #+#             */
/*   Updated: 2023/06/10 13:39:19 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkformat(va_list args, char const letter)
{
	if (letter == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (letter == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (letter == 'p')
	{
		write(1, "0x", 2);
		return (ft_putptr(va_arg(args, unsigned long)));
	}
	if (letter == 'd' || letter == 'i')
		return (ft_putnbr(va_arg(args, long int)));
	if (letter == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	if (letter == 'x')
		return (ft_puthexlower(va_arg(args, unsigned long)));
	if (letter == 'X')
		return (ft_puthexupper(va_arg(args, unsigned long)));
	if (letter == '%')
		return (write(1, "%%", 1));
	return (0);
}

int	ft_printf(char const *format, ...)
{
	int		size;
	va_list	p;

	size = 0;
	va_start(p, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
		size += ft_checkformat(p, *format);
		}
		else
		{
			write(1, format, 1);
		size++;
		}
	format ++;
	}
	va_end(p);
	return (size);
}
