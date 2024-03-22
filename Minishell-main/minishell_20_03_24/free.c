/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:43:59 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/21 23:33:42 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_deletenod(t_data *g_data)
{
	t_data_list	*temp;

	temp = 0;
	if (g_data->cmd_lst->next != 0)
		temp = g_data->cmd_lst->next;
	free (g_data->cmd_lst);
	g_data->cmd_lst = temp;
}

void	ft_free_matrix(t_data *g_data, int n)
{
	if (n == 0)
	{
		while (g_data->cmd_lst->cmd[g_data->x])
		{
			free(g_data->cmd_lst->cmd[g_data->x]);
			if (g_data->cmd_rute != NULL)
				free(g_data->cmd_rute);
			g_data->x++;
		}
		free(g_data->cmd_lst->cmd);
		if (g_data->cmd_rute != NULL)
			free(g_data->cmd_rute);
	}
	else
	{
		if (g_data->b_env == 0)
		{
			while (g_data->cmd_paths[g_data->x])
			{
				free(g_data->cmd_paths[g_data->x]);
				g_data->x++;
			}
			free(g_data->cmd_paths);
		}
	}
}

void	ft_free_all(t_data *g_data)
{
	ft_backward_node(g_data);
	g_data->x = 0;
	if ((g_data->cmd_lst->infile_tag == 0 || g_data->cmd_lst->infile_tag == 4)
		&& g_data->cmd_lst->outfile_tag == 0 && g_data->cmd_lst->next == 0)
		ft_free_matrix(g_data, 0);
	while (g_data->cmd_lst && g_data->cmd_lst->next != 0)
	{
		g_data->x = 0;
		if ((g_data->cmd_lst->infile_tag == 0
				|| g_data->cmd_lst->infile_tag == 4)
			&& g_data->cmd_lst->outfile_tag == 0)
			ft_free_matrix(g_data, 0);
		free (g_data->cmd_lst->cmdaux);
		g_data->cmd_lst = g_data->cmd_lst->next;
	}
	free (g_data->cmd_lst->cmdaux);
	g_data->x = 0;
	if (g_data->b_env == 0)
		ft_free_matrix(g_data, 1);
	ft_backward_node(g_data);
	while (g_data->cmd_lst)
		ft_deletenod(g_data);
}

void	ft_free_end(t_data *g_data, t_env	*envp)
{
	t_env	*aux;

	aux = NULL;
	free(g_data->env_p);
	while (envp)
	{
		aux = 0;
		if (envp->next != 0)
			aux = envp->next;
		if (envp->value != NULL)
			free(envp->value);
		free (envp);
		envp = aux;
	}
	free(envp);
	free(g_data);
}
