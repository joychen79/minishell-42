/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:10:26 by rrimonte          #+#    #+#             */
/*   Updated: 2024/02/26 14:35:50 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_actualize_env(t_data *g_data, t_env	*envp)
{
	t_env	*head = NULL;
	int env_count;
	int i;

	env_count = 0;
	head = envp;
	while(envp)
	{
		env_count++;
		envp = envp->next;
	}
	envp = head;
	if(g_data->env_p != NULL)
	{
		printf("libero>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<\n");
		free(g_data->env_p);
	}
	g_data->env_p = (char**) malloc (sizeof(char *) * env_count);
	i = 0;
	printf("***********************************************************************************\n");
	while(envp)
	{
		g_data->env_p[i] = envp->value;
		printf("|%s|\n",g_data->env_p[i]);
		
		envp = envp->next;
		i++;
	}
	printf("***********************************************************************************\n");
	envp = head;
}