/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:28:44 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/26 15:33:16 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_join(t_data *g_data)
{
	t_data_list	*del;
	char		*straux;

	straux = NULL;
	g_data->cmd_count--;
	g_data->total_count--;
	del = g_data->cmd_lst->next;
	straux = (char *)malloc (sizeof(char)
			* ft_strlen(g_data->cmd_lst->cmdaux) + 1);
	ft_strlcpy(straux, g_data->cmd_lst->cmdaux,
		ft_strlen(g_data->cmd_lst->cmdaux) + 1);
	g_data->cmd_lst->cmdaux = ft_strjoin(straux, del->cmdaux,
			g_data->cmd_lst->next->bjoin);
	free(straux);
	g_data->cmd_lst->next = del->next;
	if (g_data->cmd_lst->next != 0)
		g_data->cmd_lst->next->previous = g_data->cmd_lst;
	free(del->cmdaux);
	free(del);
}

void	ft_order_outfiles(t_data *g_data)
{
	t_data_list	*temp;
	t_data_list	*aux;

	if (g_data->border == 0)
	{
		if (g_data->cmd_lst->outfile_tag == 1 && g_data->cmd_lst->next != 0
			&& g_data->cmd_lst->s_tg == g_data->cmd_lst->next->s_tg)
		{
			if (g_data->cmd_lst->next->outfile_tag == 0)
			{
				temp = g_data->cmd_lst;
				aux = g_data->cmd_lst->next;
				temp->next = aux->next;
				aux->previous = temp->previous;
				aux->next = temp;
				temp->previous = aux;
				if (temp->next != NULL)
					temp->next->previous = temp;
				if (aux->previous != NULL)
					aux->previous->next = aux;
				g_data->cmd_lst = g_data->cmd_lst->previous;
				g_data->borderaux = 1;
			}
		}
	}
}

void	ft_order_infiles(t_data *g_data)
{
	t_data_list	*temp;
	t_data_list	*aux;

	if (g_data->cmd_lst != 0 && g_data->cmd_lst->infile_tag == 1
		&& g_data->cmd_lst->previous != 0
		&& g_data->cmd_lst->s_tg == g_data->cmd_lst->previous->s_tg)
	{
		if (g_data->cmd_lst->previous->infile_tag == 0)
		{
			temp = g_data->cmd_lst;
			aux = g_data->cmd_lst->previous;
			aux->next = temp->next;
			temp->previous = aux->previous;
			if (aux->previous != NULL)
				aux->previous->next = temp;
			temp->next = aux;
			aux->previous = temp;
			if (g_data->cmd_lst == temp)
				g_data->cmd_lst = aux;
			if (g_data->cmd_lst->next != 0)
				g_data->cmd_lst->next->previous = g_data->cmd_lst;
			g_data->borderaux = 1;
		}
	}
}
