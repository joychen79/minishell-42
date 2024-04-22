/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/20 10:51:28 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

t_env	*new_env(char *str)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (!tmp)
		return (NULL);
	tmp->value = (char *)malloc (sizeof(char) * ft_strlen(str) + 1);
	ft_strlcpy(tmp->value, str, ft_strlen(str) + 1);
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

char	**if_no_env(char **str)
{
	char	*oldpwd;
	char	*pwd;
	char	**newstr;
	char	*shlvl;

	newstr = (char **)malloc(sizeof(char *) * 4);
	if (!newstr)
		return (NULL);
	pwd = get_new_path();
	oldpwd = "OLDPWD";
	shlvl = "SHLVL=0";
	if (!str || !*str)
	{
		newstr[0] = pwd;
		newstr[1] = oldpwd;
		newstr[2] = shlvl;
		newstr[3] = NULL;
	}
	return (newstr);
}

t_env	*get_env(char **str)
{
	t_env	*aux;
	t_env	*env;
	int		i;
	int		noenv;

	env = NULL;
	i = 0;
	noenv = 0;
	if (*str == NULL)
	{
		str = if_no_env(str);
		noenv = 1;
	}
	while (str[i])
	{
		aux = new_env(str[i]);
		addenv_back(&env, aux);
		i++;
	}
	if (noenv == 1)
		freestr (str);
	return (env);
}
