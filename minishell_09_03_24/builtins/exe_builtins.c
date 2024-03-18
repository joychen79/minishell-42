/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:10:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/18 19:52:01 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

static void	exec_builtin_util(char **argv, t_env *env)
{
	if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
		g_exit_status = ft_echo(argv);
	if ((ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0))
	{
		g_exit_status = ft_pwd();
	}
	if (ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
		g_exit_status = ft_env(env);
	exit(g_exit_status);
}

void	exec_builtin(char **argv, t_env *env)
{
	int	i;

	i = 1;
	if (ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0)
	{
		if (!argv[1])
			g_exit_status = print_export(env);
		while (argv[i])
			g_exit_status = ft_export(env, argv[i++]);
	}
	else if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
	{
		while (argv[i])
			g_exit_status = ft_unset(&env, argv[i++]);
	}
	else if (ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
		g_exit_status = ft_cd(argv[1], env);
	else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0]))
		|| !ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]))
		|| !ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
		exec_builtin_util(argv, env);
}
