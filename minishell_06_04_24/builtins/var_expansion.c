/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/07 15:42:27 by jingchen         ###   ########.fr       */
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
	int		valid;
	char	*valid_name;

	printf("explotttooooooowiii\n");
	i = 1;
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

	i = 0;
	printf(">>>>>>>>>>%s\n", env->value);
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
	printf("explotttooooooowiii\n");
	printf(">>>>>>>>>>%s\n", env->value);
	if (!var_exp)
		return (NULL);
	while (env)
	{
		printf("*********%s\n", env->value);
		if (is_existing (&env, var_exp) == 1)
		{
			printf("*********%s\n", env->value);
			expenssion = envvalue(env->value);
			printf("*********%s\n", env->value);
		}
		printf("<<<<<<111111111>>>>>\n");
		printf("%s\n",env->value);
		printf("<<<<<<333333>>>>>\n");
		env = env->next;
		printf("<<<<<<222222222>>>>>\n");
	}
	printf("explotttooooooowiii\n");
	free(var_exp);
	printf("explotttooooooowiii\n");
	return (expenssion);
}
