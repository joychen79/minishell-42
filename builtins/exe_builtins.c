/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:10:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/07 12:00:57 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **argv, t_env *env)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, env);
	if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(argv[0], "env") == 0)
		ft_env(env);
	if (ft_strcmp(argv[0], "export") == 0)
		export(env, argv);
	if (ft_strcmp(argv[0], "unset") == 0)
		unset(&env, argv);
}
