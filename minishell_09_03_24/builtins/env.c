/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/17 13:31:19 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

int	ft_env(t_env *env)
{
	if (!env)
	{
		g_exit_status = 1;
		return (1);
	}
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
