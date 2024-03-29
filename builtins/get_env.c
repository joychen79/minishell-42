/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/26 18:49:19 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;


t_env	*new_env(char *str)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->value = str;
	tmp->next = NULL;
	return (tmp);
}

void	addenv_back(t_env **env, t_env *new)
{
	t_env	*aux;

	if (!env)
		return ;
	if (*env)
	{
		aux = *env;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*env = new;
}

t_env	**get_env(char **str)
{
	t_env	*aux;
	t_env	*env;
	t_env	**res;
	int		i;

	env = NULL;
	i = 0;
	while (str[i])
	{
		aux = new_env(str[i]);
		addenv_back(&env, aux);
		i++;
	}
	res = &env;
	return (res);
}

/*t_env	*get_env(char **str)
{
	t_env	*aux;
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (str[i])
	{
		aux = new_env(str[i]);
		addenv_back(&env, aux);
		i++;
	}
	return (env);
}*/
/*int	env_size(t_env **env)
{
	int	size;

	size = 0;
	if (!env)
		return (0);
	while (*env)
	{
		*env = (*env)->next;
		size++;
	}
	return (size);
}*/
