/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:13:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/19 18:42:19 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

static char	*find_lvl(t_env	*env)
{
	char	*value_shell;
	char	*name;

	value_shell = NULL;
	while (env)
	{
		name = var_name(env->value);
		if (!ft_strncmp("SHLVL", name, ft_strlen(name)))
		{
			value_shell = envvalue(env->value);
			free(name);
			break ;
		}
		free(name);
		env = env->next;
	}
	return (value_shell);
}

void	increment_shlv(t_env *env)
{
	int		shell_lv;
	char	*value_shell;
	char	*new_shlvl;
	char	*new_shlvlaux;

	value_shell = find_lvl(env);
	shell_lv = ft_atoi(value_shell) + 1;
	new_shlvlaux = ft_itoa(shell_lv);
	new_shlvl = ft_strjoin("SHLVL=", new_shlvlaux, 0);
	ft_export(env, new_shlvl);
	free(new_shlvlaux);
	free(new_shlvl);
}
