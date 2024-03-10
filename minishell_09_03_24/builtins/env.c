/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 16:01:34 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

/*int	ft_env(char **str)
{
	t_env	*env;

	env = get_env(str);
	while (env)
	{
		ft_printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}*/

int	ft_env(t_env *env)
{
	if (!env)
	{
		g_exit_status = 1;
		return (0);
	}
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	g_exit_status = 0;
	return (0);
}
