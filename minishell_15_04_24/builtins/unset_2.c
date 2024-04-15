/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/10 23:26:37 by rrimonte         ###   ########.fr       */
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
