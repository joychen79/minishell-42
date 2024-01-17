/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/17 20:33:07 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

//se puede gestionar con funcion de echo, pero tambien se debería poder gestionar con entrada y salida de comanndo.
// Por otro lado, cuando se lee el commando con Readline, se deberia reconocer el $ como varia cuando no hay comillas o con comilla doble, pero con comilla simple, se debe conocer como el sinbolo tal cual.
// se gestiona el g_exit_satus con waitpid.
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

/*char	*parsing_doller(char *argv)
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
}*/

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
	return (expenssion);
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
		{
			status = ft_itoa(g_exit_status);
		}
		i++;
	}
	return (status);
}*/

/*char	*var_expansion(char *argv, t_env *env)
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
}*/

/*void	echo_expansion(char **argv, t_env *env)
{
		int i;
		i = 2;
		int j;
	//	char *value;
		(void)env;
		
		if(!strncmp(argv[1], "echo", ft_strlen(argv[1])))
		{
			while(argv[i])
			{
				j = 0;
				while(argv[i][j])
				{
					if(argv[i][j] != '$')
						{
							ft_printf("%c", argv[i][j]);
		
						}
				if(argv[i][j] == '$')
					{
						if(argv[i][j+1] == '?')
							{
								printf("%d", g_exit_status);
								j++;
							}
						if (argv[i][j+1] && ((ft_isalnum(argv[i][j+1]) || argv[i][j+1] == '_')))
						{
							value = var_expansion(argv[i], env);
								printf("%s", value);
							while(*value)
							{	
								value++;
								j++;
							}
						}
						j++;
				}
				i++;
					if(argv[i])
						ft_printf(" ");
				}
			}
		
}*/