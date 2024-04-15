/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 21:45:08 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/15 01:25:40 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

extern int	g_exit_status;

void	create_pipes_end(t_data *g_data, int *pid, int child_pid)
{
	dup2(g_data->in_std, STDIN_FILENO);
	close(g_data->in_std);
	g_data->bclose = 1;
	ft_backward_node(g_data);
	ft_forward_node(g_data);
	if (g_data->bexit == 0)
	{
		g_data->i = 0;
		while (g_data->i < g_data->cmd_count)
		{
			child_pid = waitpid(pid[g_data->i], &g_data->status, 0);
			printf("espero al hijo |%d|\n",g_data->i);
			if (child_pid == -1)
			{
				perror("Error waiting the child process");
				exit(EXIT_FAILURE);
			}
			g_exit_status = (g_data->status >> 8) & 0xFF;
			g_data->i++;
		}
	}
	else
		ft_exit(g_data, pid, child_pid);
}

int	create_pipes1(t_data *g_data, t_env *envp)
{
	ft_check_infiles(g_data);
	if (g_data->cmd_count == 1 && g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0)
	{
		if (1 == exec_exit_father(g_data))
			return (1);
		if (exec_builtins_father(g_data, envp) == 1)
			return (1);
	}
	return (0);
}

void	create_pipes2(t_data *g_data)
{
	while ((g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2)
		&& g_data->total_count > 0)
	{
		if (g_data->cmd_lst->outfile_tag == 2)
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_TRUNC | O_RDWR | O_CREAT, 0664);
		g_data->total_count--;
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
	}
	if (g_data->cmd_lst->infile_tag == 2)
	{
		g_data->total_count = g_data->total_count - 1;
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
	}
}

int	*create_pipes3(t_data *g_data, t_env *envp, int *pid)
{
	printf("**********************************************\n");
	if (g_data->cmd_lst->cmd != 0)
		printf("antes cmd-->|%s|\n", g_data->cmd_lst->cmd[0]);
	printf("infile-->|%d|\n", g_data->cmd_lst->infile_tag);
	printf("outfile-->|%d|\n", g_data->cmd_lst->outfile_tag);
	printf("I-->|%d|\n", g_data->i);
	printf("Total count-->|%d|\n", g_data->total_count);
	printf("bexport-->|%d|\n", g_data->cmd_lst->bexport);
	printf("**********************************************\n");
	if (g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0
		&& g_data->i <= g_data->total_count
		&& pid[g_data->i] == 0 && g_data->cmd_lst->bexport == 0)
	{
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		printf("cmd-->|%s|\n", g_data->cmd_lst->cmd[0]);
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

		child(g_data, envp);
	}
	else
	{
		if (g_data->cmd_lst->previous != NULL
			&& g_data->cmd_lst->previous->infile_tag == 2)
			close(g_data->cmd_lst->previous->fd[WRITE_O]);
		close(g_data->cmd_lst->fd[WRITE_O]);
		if (g_data->i < g_data->total_count - 1
			&& g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		if (g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2)
			g_data->total_count = g_data->total_count - 1;
		g_data->i++;
	}
	return (pid);
}

int	*new_pipe(t_data *g_data, int *pid)
{
	if (g_data->cmd_lst->infile_tag == 0
		&& g_data->cmd_lst->outfile_tag == 0
		&& g_data->i <= g_data->total_count
		&& g_data->cmd_lst->bexport == 0)
	{
		printf("I----->%d\n", g_data->i);
		pipe(g_data->cmd_lst->fd);
		pid[g_data->i] = fork();
	}
	return (pid);
}
