/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:10:22 by jingchen          #+#    #+#             */
/*   Updated: 2023/12/30 14:16:35 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int		is_builtin(char *command)
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

int		exec_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		result = echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = cd(args, env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, env, mini->secret_env);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, &env);
	return (result);
}