/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/16 16:47:58 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

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
	while (env)
	{
		ft_printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
