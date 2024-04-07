/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/07 15:01:34 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

static t_env	**unset_util(t_env **env, char *argv)
{
	t_env	*tmp;
	char	*straux2;

	straux2 = var_name((*env)->value);
	env = libera_primera(env, argv);
	if (env && *env)
	{
		while (*env && !(ft_strncmp(straux2, argv, ft_strlen(argv))))
		{
			free(straux2);
			tmp = *env;
			*env = (*env)->next;
			free(tmp->value);
			free(tmp);
			straux2 = var_name((*env)->value);
		}
		free(straux2);
	}
	else
		free(straux2);
	return (env);
}

static int	check_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
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
	t_env	**aux;

	aux = env;
	if (!aux || !*aux || check_argv(argv) == 1)
		return (1);
	aux = unset_util(env, argv);
	/*while (!aux)
	{
		printf("%s\n", (*aux)->value);
		*aux = (*aux)->next;
		printf("******************holaaaaaaaaaa estoy aqui");
	}*/
	ft_unset2(aux, argv);
	env = aux;
	return (0);
}

/*int ft_unset(t_env **env, char *argv)
{
	t_env	*cur;
	char	*straux2;

	if (*env == NULL || check_argv(argv) == 1)
	{
		printf("hola\n");
		return (1);
	}
	cur = *env;
	straux2 = var_name(cur->value);
	if (!(ft_strncmp(straux2, argv, ft_strlen(argv))))
	{
		free(*env);
		cur = cur->next;
		ft_unset(env, argv);
	}
	else
	{
		cur = *env;
		ft_unset(&cur->next, argv);
	}
	if (!(*env)->next && !(ft_strncmp(straux2, argv, ft_strlen(argv))))
	{
		cur = *env;
		*env = NULL;
		free(cur);
	}
	free (straux2);
	return (0);
}*/
