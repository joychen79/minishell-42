/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/05 20:13:27 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern	int	g_exit_status;

char	*var_name(char	*argv)
{
	char	*name;
	int		i;

	i = 0;
	if (!argv)
		return (NULL);
	name = NULL;
	while (argv[i])
	{
		if (argv[i] == '=')
		{
			name = ft_substr(argv, (int)0, i);
			break ;
		}
		i++;
	}
	if (argv[i] == '\0')
		name = ft_substr(argv, (int)0, i);
	return (name);
}

/*static t_env	**libera_primera(t_env **env, char *argv)
{
		t_env	*tmp;
		char	*straux2;
		//t_env	**aux;

		//aux = env;

	straux2 = var_name((*env)->value);
	if (env && *env && !(ft_strncmp(straux2, argv, ft_strlen(argv))))
	{
			free(straux2);
			tmp = *env;
			*env = tmp->next;
			env = &(*env);
			free(tmp);
	}
		return (env);
}*/

/*static t_env	**unset_util(t_env **env, char *argv)
{
	t_env	*tmp;
	char	*straux2;

	straux2 = var_name((*env)->value);
	//env = libera_primera(env, argv);
		//printf("********************** pasando por primera\n");
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
			printf("********************** pasando por segunda vez\n");
		}
		free(straux2);
	}
	return (env);
}*/

/*static void	swap(t_env *aux)
{
	t_env	*tmp;

	tmp = aux->next;
	aux->next = tmp->next;
	free(tmp->value);
	free(tmp);
}*/

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

/*int	ft_unset(t_env **env, char *argv)
{
	t_env	*aux;
	char	*straux2;

	if (!env || !*env || check_argv(argv) == 1)
		return (1);
	env = unset_util(env, argv);
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
	return (0);
}*/

/*void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (begin_list == NULL || *begin_list == NULL)
		return;

	t_list *cur = *begin_list;

	if (cmp(cur->data, data_ref) == 0)
	{
		*begin_list = cur->next;
		free(cur);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	cur = *begin_list;
	ft_list_remove_if(&cur->next, data_ref, cmp);
}*/

int ft_unset(t_env **env, char *argv)
{
	t_env	*cur;
	char	*straux2;
	t_env	**aux;

	if (*env == NULL || check_argv(argv) == 1)
	{
		return (1);
	}
	
	aux = env;
	while (*aux)
	{
		straux2 = var_name((*aux)->value);
		printf("**************** mi llamo %s\n", straux2);
		if (!(ft_strncmp(straux2, argv, ft_strlen(straux2))))
			break ;
		*aux = (*aux)->next;
	}
		straux2 = var_name((*aux)->value);
		printf("**************** mi llamo %s OTRA VEZ\n", straux2);
		if (*aux && !(ft_strncmp(straux2, argv, ft_strlen(straux2))))
		{
			cur = *aux;
			*aux = cur->next;
			free(cur->value);
			free(cur);
		}
			free(straux2);
		aux = env;
	return (0);
}