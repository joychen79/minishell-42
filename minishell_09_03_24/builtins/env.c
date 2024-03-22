/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/22 18:33:17 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

int	empty_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '=')
		{
			return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_env(t_env *env)
{
	//if (!env)
	//{
	//	return (1);
	//}
	while (env)
	{
		if (empty_value(env->value) == 1)
			printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
