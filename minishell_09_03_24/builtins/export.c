/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:56 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/03 18:55:21 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

int	is_existing(t_env **env, char *name)
{
	int		exist_len;
	int		new_len;
	char	*tmp;
	t_env	*aux;

	aux = *env;
	new_len = ft_strlen(name);
	if (!env || name == NULL)
		return (-1);
	while (aux)
	{
		tmp = var_name(aux->value);
		exist_len = ft_strlen(tmp);
		if ((exist_len == new_len)
			&& (!(ft_strncmp(tmp, name, exist_len))))
		{
			free(tmp);
			return (1);
		}
		free(tmp);
		aux = aux->next;
	}
	return (0);
}

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

	if (!env)
		return (1);
	i = 0;
	sorted = sort_env(env);
	while (sorted)
	{
		name = var_name(sorted->value);
		value = envvalue(sorted->value);
		if (empty_value(sorted->value) == 1)
			printf("declare -x %s=\"%s\"\n", name, value);
		else
			printf("declare -x %s\n", name);
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

	if (!env)
		return (1);
	name = var_name(argv);
	aux = new_env(argv);
	if (is_existing (&env, name) == 1)
	{
		ft_unset (&env, name);
		addenv_back (&env, aux);
	}
	if (!is_existing(&env, name) || !env)
	{
		addenv_back(&env, aux);
			printf("********************** OTRA VEZ NEW\n");
	}
	free(name);
	return (0);
}
