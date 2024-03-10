/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:01 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/10 16:22:52 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int valid_n_option (char *argv)
{
	int i;
	
	i = 1;
	while (argv[i])
		{
			if (argv[0] == '-' && argv[i] == 'n')	
				i++;
		}
	if(!argv[i])
		return (1);
	else 
		return (0);
}

int	ft_echo(char **args)
{
	int		i;
	int		j;
	int		n_option;

	i = 2;
	j = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && ((ft_strncmp(args[i], "-n", ft_strlen(args[i])) == 0) || valid_n_option (args[i])))
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
