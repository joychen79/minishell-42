/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/22 00:55:49 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern int	g_exit_status;

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
	char	*valid_name;

	i = 0;
	j = 0;
	valid_name = NULL;
	while (argv[i])
	{
		if (argv[i] == '$')
			break ;
		i++;
	}
	i++;
	j = i;
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

	i = 0;
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
	if (!var_exp)
		return (NULL);
	while (env)
	{
		if (is_existing (&env, var_exp) == 1)
			expenssion = envvalue(env->value);
		env = env->next;
	}
	free(var_exp);
	return (expenssion);
}
