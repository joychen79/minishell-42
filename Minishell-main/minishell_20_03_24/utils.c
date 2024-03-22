/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:10:26 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/21 23:55:13 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_actualize_env(t_data *g_data, t_env	*envp)
{
	t_env	*head;
	int		env_count;
	int		i;

	env_count = 0;
	head = envp;
	while (envp)
	{
		env_count++;
		envp = envp->next;
	}
	envp = head;
	if (g_data->env_p != NULL)
		free(g_data->env_p);
	g_data->env_p = (char **) malloc (sizeof(char *) * env_count);
	i = 0;
	while (envp)
	{
		g_data->env_p[i] = envp->value;
		envp = envp->next;
		i++;
	}
	envp = head;
}
