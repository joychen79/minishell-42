/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:56 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/17 13:29:49 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

t_env	*sort_env(t_env *env)
{
	char	*aux;
	t_env	*tmp;
	int		i;

	tmp = env;
	while (env->next != NULL)
	{
		i = 0;
		while (env->value[i] && (env->value[i] == env->next->value[i]))
			i++;
		if (env->value[i] > env->next->value[i])
		{
			aux = env->value;
			env->value = env->next->value;
			env->next->value = aux;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

int	print_export(t_env *env)
{
	int		i;
	t_env	*sorted;
	char	*name;
	char	*value;

	i = 0;
	sorted = sort_env(env);
	while (sorted)
	{
		name = var_name(sorted->value);
		value = envvalue(sorted->value);
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		sorted = sorted->next;
	}
	free(sorted);
	return (0);
}

int	ft_export(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;

	if (!argv)
		return (0);
	name = var_name(argv);
	aux = new_env(argv);
	if (is_existing (&env, name) == 1)
	{
		ft_unset (&env, name);
		addenv_back (&env, aux);
	}
	if (!is_existing(&env, name))
	{
		addenv_back(&env, aux);
	}
	free(name);
	return (0);
}
