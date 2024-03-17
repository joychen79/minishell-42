/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/17 14:11:23 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

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

int	is_existing(t_env **env, char *name)
{
	int		exist_len;
	int		new_len;
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
			free(tmp);
			return (1);
		}
		free(tmp);
		aux = aux->next;
	}
	return (0);
}

/*void	ft_unset_primer(t_env **env, char *argv)
{
	t_env	*tmp;
	t_env	*aux;
	char	*straux2;

	if (!env || !*env || !argv)
		return ;
	straux2 = var_name((*env)->value);
	while (*env && !(ft_strncmp(straux2, argv, ft_strlen(straux2))))
	{
		free(straux2);
		tmp = *env;
		*env = (*env)->next;
		free(tmp->value);
		free(tmp);
		straux2 = var_name((*env)->value);
	}
	free(straux2);
	aux = *env;
}

int	ft_unset(t_env **env, char *argv)
{
	t_env	*tmp;
	t_env	*aux;
	char	*straux2;

	if (!env || !*env || !argv)
		return (1) ;
	straux2 = var_name((*env)->value);
	ft_unset_primer(env, argv);
	aux = *env;
	if (aux->next != NULL)
		straux2 = var_name(aux->next->value);
	while (aux && aux->next)
	{
		if (!(ft_strncmp(straux2, argv, ft_strlen(straux2))))
		{
			tmp = aux->next;
			aux->next = tmp->next;
			free(tmp->value);
			free(tmp);
		}
		aux = aux->next;
		if (aux && aux->next != NULL)
			free(straux2);
		if (aux && aux->next != NULL)
			straux2 = var_name(aux->next->value);
	}
	free(straux2);
	return (0);
}*/

void	ft_unset(t_env **env, char *argv)
{
	t_env	*tmp;
	t_env	*aux;
	char	*straux;
	char	*straux2;

	if (!env || !*env || !argv)
		return ;
	straux = var_name(argv);
	straux2 = var_name((*env)->value);
	while (*env && !(ft_strncmp(straux2, straux, ft_strlen(straux2))))
	{
		free(straux);
		free(straux2);
		tmp = *env;
		*env = (*env)->next;
		free(tmp->value);
		free(tmp);
		straux = var_name(argv);
		straux2 = var_name((*env)->value);
	}
	free(straux);
	free(straux2);
	aux = *env;
	straux = var_name(argv);
	if (aux->next != NULL)
		straux2 = var_name(aux->next->value);
	while (aux && aux->next)
	{
		if (!(ft_strncmp(straux2, straux, ft_strlen(straux2))))
		{
			free(straux);
			tmp = aux->next;
			aux->next = tmp->next;
			free(tmp->value);
			free(tmp);
			straux = var_name(argv);
		}
		aux = aux->next;
		if (aux && aux->next != NULL)
			free(straux2);
		if (aux && aux->next != NULL)
			straux2 = var_name(aux->next->value);
	}
	free(straux);
	free(straux2);
	g_exit_status = 0;
}
