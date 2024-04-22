/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/19 18:57:42 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

t_env	**libera_primera(t_env **env, char *argv)
{
	t_env	*tmp;
	char	*straux2;

	straux2 = var_name((*env)->value);
	if (*env && !(ft_strncmp(straux2, argv, ft_strlen(straux2))))
	{
		free(straux2);
		tmp = (*env)->next;
		free(*env);
		*env = tmp;
	}
	else
		free(straux2);
	return (env);
}

void	swap(t_env *aux)
{
	t_env	*tmp;

	tmp = aux->next;
	aux->next = tmp->next;
	free(tmp->value);
	free(tmp);
}

static int	check_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if ((!ft_isalnum(argv[i]) && argv[i] != '_')
			|| (!ft_isalpha(argv[0]) && argv[0] != '_'))
		{
			printf("unset : \'%s\' : is invalid identifier\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset2(t_env **env, char *argv)
{
	t_env	*aux;
	char	*straux2;

	aux = *env;
	if (aux->next != NULL)
		straux2 = var_name(aux->next->value);
	while (aux && aux->next)
	{
		if (!(ft_strncmp(straux2, argv, ft_strlen(argv))))
			swap(aux);
		aux = aux->next;
		if (aux && aux->next != NULL)
		{
			free(straux2);
			straux2 = var_name(aux->next->value);
		}
	}
	free(straux2);
}

int	ft_unset(t_env **env, char *argv)
{
	if (!env || !*env || check_argv(argv) == 1)
		return (1);
	env = libera_primera(env, argv);
	ft_unset2(env, argv);
	return (0);
}
