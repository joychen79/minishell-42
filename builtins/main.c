/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:23:25 by jingchen          #+#    #+#             */
/*   Updated: 2023/11/26 13:21:11 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		if (!(ft_strncmp("pwd", av[1], ft_strlen(av[1]))))
			ft_pwd ();
		else if(!(ft_strncmp("echo", av[1], ft_strlen(av[1]))))
			ft_echo(av);
		else if(!(ft_strncmp("myenv", av[1], ft_strlen(av[1]))))
			ft_env(env);
		else if(!(ft_strncmp("envsize", av[1], ft_strlen(av[1]))))
			ft_printf("%d\n", env_size(get_env(env)));
	}
	return (0);
}
