/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:33:14 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/06 21:56:55 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

extern int	g_exit_status;

void	ft_init_here_docs2(t_data *g_data, int	*pid)
{
	int	child_pid;

	child_pid = 0;
	if (g_data->cmd_lst->infile_tag == 2 && pid[g_data->x] == 0)
	{
		ft_here_doc_file(g_data);
		g_data->x++;
	}
	else
	{
		if (g_data->cmd_lst->infile_tag == 2)
		{
			child_pid = waitpid(pid[g_data->x], &g_data->status, 0);
			if (child_pid == -1)
			{
				perror("Error al esperar here_doc");
				exit(EXIT_FAILURE);
			}
			if (g_data->status == 2)
				return ;
		}
		g_data->i++;
		if (g_data->cmd_lst->next != NULL)
			g_data->cmd_lst = g_data->cmd_lst->next;
	}
}

void	ft_init_here_docs(t_data *g_data)
{
	int	*pid;

	pid = NULL;
	if (g_data->herecount != 0)
	{
		pid = (int *)malloc (sizeof(int) * g_data->herecount);
		if (pid == NULL)
			exit(0);
		g_data->i = 0;
		g_data->x = 0;
		while (g_data->i <= g_data->total_count - 1)
		{
			if (g_data->cmd_lst->infile_tag == 2)
			{
				pipe(g_data->cmd_lst->fd);
				pid[g_data->x] = fork();
			}
			ft_init_here_docs2(g_data, pid);
		}
		free(pid);
	}
}
