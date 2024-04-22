/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:16:59 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/22 06:50:10 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

extern int	g_exit_status;

int	exec_exit_father(t_data *g_data)
{
	if (g_data->cmd_lst->cmd[0] != NULL)
	{
		if (g_data->cmd_lst->cmd != NULL
			&& ft_strncmp(g_data->cmd_lst->cmd[0]
				, "exit", ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0)
		{
			g_data->total_count--;
			g_data->cmd_count--;
			g_data->bexit = 1;
			if (g_data->cmd_lst->cmd[1] != NULL)
			{
				if (g_data->cmd_lst->cmd[2] != NULL)
					perror("to many arguments\n");
				else
					g_exit_status = ft_atoi(g_data->cmd_lst->cmd[1]);
			}
			return (1);
		}
	}
	return (0);
}

t_env	*exec_builtins_father(t_data *g_data, t_env *envp)
{
	if (g_data->cmd_lst->cmd[0] != NULL)
	{
		if (g_data->cmd_lst->cmd != NULL
			&& (ft_strncmp(g_data->cmd_lst->cmd[0], "export",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0
				|| ft_strncmp(g_data->cmd_lst->cmd[0], "unset",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0
				|| ft_strncmp(g_data->cmd_lst->cmd[0], "cd",
					ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0))
		{
			envp = exec_builtin(g_data->cmd_lst->cmd, envp);
			ft_actualize_env(g_data, envp);
			g_data->total_count--;
			g_data->cmd_count--;
			g_data->cmd_lst->infile_tag = 4;
			if (g_data->cmd_lst->next != 0)
				g_data->cmd_lst = g_data->cmd_lst->next;
		}
	}
	return (envp);
}

int	*init_pid(t_data *g_data, int *pid)
{
	signal(SIGINT, signal_father);
	signal(SIGQUIT, SIG_IGN);
	if (g_data->cmd_count != 0)
	{
		pid = (int *)malloc (sizeof(int) * g_data->cmd_count);
		if (pid == NULL)
			exit(0);
	}
	return (pid);
}

t_env	*create_pipes(t_data *g_data, t_env	*envp)
{
	int	*pid;

	pid = NULL;
	pid = init_pid(g_data, pid);
	ft_init_here_docs(g_data);
	ft_backward_node(g_data);
	if (g_data->status == 2)
		return (envp);
	g_data->i = 0;
	g_data->z = -1;
	g_data->cmd_total = g_data->cmd_count;
	while (g_data->i <= g_data->total_count - 1)
	{
		envp = create_pipes1(g_data, envp);
		if (g_data->bexit == 1)
			break ;
		create_pipes2(g_data);
		pid = new_pipe(g_data, pid);
		pid = create_pipes3(g_data, envp, pid);
	}
	create_pipes_end(g_data, pid, 0);
	if (pid != NULL)
		free(pid);
	return (envp);
}

void	ft_exit(t_data *g_data, int *pid, int child_pid)
{
	int	x;

	x = 0;
	g_data->total_count--;
	while (g_data->total_count > 0)
	{
		child_pid = waitpid(pid[x], &g_data->status, 0);
		if (child_pid == -1)
		{
			perror("Error waiting child process");
			exit(EXIT_FAILURE);
		}
		x++;
		g_data->total_count--;
	}
	return ;
}
