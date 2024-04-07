/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:10:26 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/07 15:36:30 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_actualize_env(t_data *g_data, t_env	*envp)
{
	t_env	*head;
	int		env_count;
	int		i;

	env_count = 0;
	head = envp;
	//envp = envp->next;
	printf("<<<<<<<<<<%s\n", envp->value);
	while (envp)
	{
		env_count++;
		envp = envp->next;
	}
	env_count++;
	envp = head;
	printf("<<<<<<<<<<%s\n", envp->value);
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
	printf("<<<<<<<<<<%s\n", envp->value);
	return(envp);
}

void	ft_order(t_data *g_data, t_env *envp)
{
	if (g_data->cmd_lst->cmdaux == NULL)
	{
		if (g_data->cmd_lst->infile_tag == 1)
			ft_error(2, g_data, envp);
		else if (g_data->cmd_lst->outfile_tag == 1)
			ft_error(3, g_data, envp);
		else
			ft_error(1, g_data, envp);
	}
	while (g_data->border == 0)
	{
		ft_backward_node(g_data);
		ft_forward_node(g_data);
	}
	ft_backward_node(g_data);
	while (g_data->cmd_lst != 0 && g_data->cmd_lst->next != 0)
	{
		ft_count_builtins(g_data, envp);
		g_data->cmd_lst = g_data->cmd_lst->next;
	}
	ft_count_builtins(g_data, envp);
}
