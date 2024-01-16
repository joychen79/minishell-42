/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/16 20:58:41 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

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

/*char	*parsing_g_exit_state(char *argv)
{
	int		i;
	char	*status;

	i = 0;
	status = NULL;
	while (argv[i])
	{
		if (argv[i] == '$' && argv[i + 1] == '?')
			break ;
		i++;
	}
	status = ft_itoa(g_exit_status);
	return (status);
}*/

char	*var_expansion(char *argv, t_env *env)
{
	char	*var_exp;
	char	*expenssion;

	var_exp = parsing_doller(argv);
	if (!var_exp)
		return (NULL);
	while (env)
	{
		if (is_existing (&env, var_exp) == 1)
			expenssion = envvalue(env->value);
		env = env->next;
	}
	return (expenssion);
}

/*void	echo_expansion(char **argv, t_env *env)
{
	//	int i;
	//	i = 1;
	//	while(argv[i])
		{
		ft_printf("%s",var_expansion(argv[1], env));
	//	if(argv[i])
	//	ft_printf(" ");
	//	i++;
	//	}
}*/