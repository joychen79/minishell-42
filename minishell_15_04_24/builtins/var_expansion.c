/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/15 19:09:55 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

//extern int	g_exit_status;
char	*envvalue(char *env)
{
	int		i;
	char	*env_value;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	env_value = ft_substr(env, i, ft_strlen(env));
	return (env_value);
}

char	*parsing_doller(char *argv)
{
	int		i;
	int		j;
	int		valid;
	char	*valid_name;

	i = 0;
	j = 0;
	valid = 0;
	valid_name = NULL;
	while (argv[i])
	{
		if (argv[i] == '$')
		{
			valid = 1;
			break ;
		}
		i++;
	}
	i++;
	j = i;
	if (valid == 0)
		i = 0;
	while (argv[i] && ((ft_isalnum(argv[i]) || argv[i] == '_')))
		i++;
	valid_name = ft_substr(argv, j, i - 1);
	return (valid_name);
}

char	*var_expansion(char *argv, t_env *env)
{
	char	*var_exp;
	char	*expenssion;
	int		i;
	int		exist_len;
	int		new_len;
	char	*tmp;
	t_env	*aux;

	i = 0;
	aux = env;
	exist_len = 0;
	expenssion = NULL;
	while (argv[i])
	{
		if (argv[i] == '$' && argv[i + 1] == '?')
		{
			expenssion = ft_itoa(g_exit_status);
		}
		i++;
	}
	var_exp = parsing_doller(argv);
	new_len = ft_strlen(var_exp);
	if (!var_exp)
		return (NULL);
	while (aux)
	{
		tmp = var_name(aux->value);
		exist_len = ft_strlen(tmp);
		if ((exist_len == new_len)
			&& (!(ft_strncmp(tmp, var_exp, exist_len))))
		{
			free(tmp);
			expenssion = envvalue(aux->value);
			break;
		}
		free(tmp);
		aux = aux->next;
	}
	free(var_exp);
	return (expenssion);
}
/*

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
			printf("env--->|%s|\n",tmp);
			free(tmp);
			return (1);
		}
		free(tmp);
		aux = aux->next;
	}
*/