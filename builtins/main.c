/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:23:25 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/17 20:37:09 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

int	main(int ac, char **av, char **env)
{
	/*if (ac > 1)
	{
		if (!(ft_strncmp("pwd", av[1], ft_strlen(av[1]))))
			ft_pwd ();
		else if(!(ft_strncmp("echo", av[1], ft_strlen(av[1]))))
			ft_echo(av);
		else if(!(ft_strncmp("myenv", av[1], ft_strlen(av[1]))))
			ft_env(env);
		else if(!(ft_strncmp("envsize", av[1], ft_strlen(av[1]))))
			ft_printf("%d\n", env_size(get_env(env)));
	}*/
	(void)ac;

	
	t_env	*envp = NULL;
	envp = get_env(env);
	//exec_builtin(av, envp);
	//ft_cd(av[2], envp);
	//int i = 2;
	/*while(av[i])
		ft_unset(&envp, av[i++]);*/
	/*while(envp)
	{
		ft_printf("%s\n", envp->value);
		envp = envp->next;
	}*/

	ft_printf("%s",var_expansion(av[1], envp));


	return (0);
}
