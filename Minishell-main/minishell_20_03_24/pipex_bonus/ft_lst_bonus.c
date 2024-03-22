/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:15:14 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/22 00:59:38 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	inicialize_var(t_data_list	*temp)
{
	temp->next = 0;
	temp->previous = 0;
	temp->tag = 0;
	temp->infile_tag = 0;
	temp->outfile_tag = 0;
	temp->s_tg = 0;
	temp->bjoin = 1;
	temp->berrorinf = 0;
	temp->bexport = 0;
	temp->cmdaux = NULL;
	temp->cmd = NULL;
	temp->fd[0] = 0;
	temp->fd[1] = 0;
	temp->bvar = 0;
}

void	inicialize_list(t_data *g_data)
{
	t_data_list	*temp;
	t_data_list	*aux;

	temp = malloc(sizeof(*temp));
	if (temp == 0)
		return ;
	inicialize_var(temp);
	if (g_data->cmd_lst == 0)
		g_data->cmd_lst = temp;
	else
	{
		aux = g_data->cmd_lst;
		g_data->cmd_lst->next = temp;
		g_data->cmd_lst = g_data->cmd_lst->next;
		g_data->cmd_lst->previous = aux;
	}
}

void	ft_close_fd(t_data *g_data)
{
	if (g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0)
		close(g_data->cmd_lst->fd[READ_O]);
}

void	ft_backward_node(t_data *g_data)
{
	while (g_data->cmd_lst != 0 && g_data->cmd_lst->previous != 0)
		g_data->cmd_lst = g_data->cmd_lst->previous;
}

void	ft_forward_node(t_data *g_data)
{
	g_data->x = 0;
	g_data->borderaux = 0;
	while (g_data->cmd_lst != 0 && g_data->cmd_lst->next != 0)
	{
		if (g_data->bclose == 1)
			ft_close_fd(g_data);
		if (g_data->cmd_lst->next != 0 && g_data->cmd_lst->next->infile_tag == 0
			&& g_data->cmd_lst->next->outfile_tag == 0
			&& g_data->cmd_lst->infile_tag == 0
			&& g_data->cmd_lst->outfile_tag == 0
			&& g_data->cmd_lst->s_tg == g_data->cmd_lst->next->s_tg)
			ft_join(g_data);
		ft_order_outfiles(g_data);
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		if (g_data->border == 0)
			ft_order_infiles(g_data);
	}
	if (g_data->bclose == 1)
		ft_close_fd(g_data);
	if (g_data->borderaux == 1)
		g_data->border = 0;
	else
		g_data->border = 1;
}
