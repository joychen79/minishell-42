/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:14:37 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/18 18:50:20 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

//extern int	g_exit_status;

int	find_dolar(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '$')
		{
			return (i);
			break ;
		}
		i++;
	}
	return (0);
}

char	*parsing_doller(char *argv)
{
	int		i;
	int		j;
	char	*valid_name;

	i = find_dolar(argv);
	valid_name = NULL;
	i = i + 1;
	j = i;
	while (argv[i] && ((ft_isalnum(argv[i]) || argv[i] == '_')))
		i++;
	valid_name = ft_substr(argv, j, i - 1);
	return (valid_name);
}

int	is_interogante(char	*argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '$' && argv[i + 1] == '?')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*find_var(char *argv, t_env *env)
{
	char	*name;
	t_env	*aux;
	char	*var_exp;
	char	*value;

	aux = env;
	value = NULL;
	var_exp = parsing_doller(argv);
	while (aux)
	{
		name = var_name(aux->value);
		if ((ft_strlen(name) == ft_strlen(var_exp))
			&& (!(ft_strncmp(name, var_exp, ft_strlen(name)))))
		{
			free(name);
			value = envvalue(aux->value);
			break ;
		}
		free(name);
		aux = aux->next;
	}
	return (value);
}

char	*var_expansion(char *argv, t_env *env)
{
	char	*expenssion;
	t_env	*aux;

	aux = env;
	expenssion = NULL;
	if (is_interogante(argv))
		expenssion = ft_itoa(g_exit_status);
	else
		expenssion = find_var(argv, aux);
	return (expenssion);
}

/*char	*parsing_doller(char *argv)
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
			break ;
		}
		free(tmp);
		aux = aux->next;
	}
	free(var_exp);
	return (expenssion);
}*/
