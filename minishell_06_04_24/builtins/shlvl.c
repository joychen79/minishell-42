/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 11:13:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/07 13:33:03 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

void	increment_shlv(t_env *env)
{
	int		shell_lv;
	char	*value_shell;
	char	*new_shlvl;
	char	*name;
	t_env	*aux;

	aux = env;
	while (env)
	{
		name = var_name(env->value);
		if (!ft_strncmp("SHLVL", name, ft_strlen(name)))
		{
			value_shell = envvalue(env->value);
			free(name);
			break ;
		}
		env = env->next;
	}
	env = aux;
	shell_lv = ft_atoi(value_shell) + 1;
	new_shlvl = ft_strjoin("SHLVL=", ft_itoa(shell_lv), 0);
	ft_export(env, new_shlvl);
	free(new_shlvl);
}
