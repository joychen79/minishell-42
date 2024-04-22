/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:25:21 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/22 06:29:57 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_prepare_outfile_child(t_data *g_data)
{
	t_data_list	*aux;

	aux = g_data->cmd_lst;
	while (g_data->cmd_lst->next != 0
		&& (g_data->cmd_lst->next->outfile_tag == 1
			|| g_data->cmd_lst->next->outfile_tag == 2))
	{
		g_data->cmd_lst = g_data->cmd_lst->next;
		if (g_data->cmd_lst->outfile_tag == 2)
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_TRUNC | O_RDWR | O_CREAT, 0664);
		if (g_data->outfl < 0)
			ft_error_exit(2);
		dup2(g_data->outfl, STDOUT_FILENO);
		close(g_data->outfl);
	}
	g_data->total_count--;
	g_data->cmd_lst = aux;
}

void	child_aux(t_data *g_data, t_env	*envp)
{
	if (g_data->cmd_lst->next == 0)
	{
		exec_builtin(g_data->cmd_lst->cmd, envp);
		if (envp != NULL)
			g_data->cmd_rute = get_cmd_path(g_data);
		execve(g_data->cmd_rute, g_data->cmd_lst->cmd, g_data->env_p);
		ft_error_exit(4);
	}
	else if (g_data->cmd_lst->next != 0
		&& (g_data->cmd_lst->next->outfile_tag == 1
			|| g_data->cmd_lst->next->outfile_tag == 2))
		ft_prepare_outfile_child(g_data);
	else
	{
		close (g_data->cmd_lst->fd[READ_O]);
		dup2(g_data->cmd_lst->fd[WRITE_O], STDOUT_FILENO);
		close (g_data->cmd_lst->fd[WRITE_O]);
	}
}

void	child(t_data *g_data, t_env	*envp)
{
	signal(SIGINT, quite_heredoc);
	signal(SIGQUIT, quite_heredoc);
	if (g_data->cmd_lst->previous != NULL)
	{
		if (g_data->cmd_lst->previous->berrorinf == 1)
			exit(1);
		if (g_data->cmd_lst->previous->infile_tag != 1)
		{
			close(g_data->cmd_lst->previous->fd[WRITE_O]);
			dup2(g_data->cmd_lst->previous->fd[READ_O], STDIN_FILENO);
			close(g_data->cmd_lst->previous->fd[READ_O]);
		}
	}
	child_aux(g_data, envp);
	if (g_data->cmd_lst->berrorinf == 1)
		exit(0);
	exec_builtin(g_data->cmd_lst->cmd, envp);
	exec_builtins_father(g_data, envp);
	if (g_data->cmd_lst->infile_tag == 4)
		exit(0);
	if (1 == exec_exit_father(g_data))
		exit(0);
	g_data->cmd_rute = get_cmd_path(g_data);
	execve(g_data->cmd_rute, g_data->cmd_lst->cmd, g_data->env_p);
	ft_error_exit(4);
}

char	*get_cmd_path(t_data *g_data)
{
	char	*tmp;
	char	*command;

	if (g_data->cmd_lst->cmd == 0)
		ft_error_exit(3);
	if (access(g_data->cmd_lst->cmd[0], X_OK) == 0)
		return (g_data->cmd_lst->cmd[0]);
	else if (g_data->b_env == 1)
		ft_error_exit(3);
	while (g_data->cmd_paths && g_data->cmd_paths[0] != NULL)
	{
		tmp = ft_strjoin(g_data->cmd_paths[0], "/", 0);
		command = ft_strjoin(tmp, g_data->cmd_lst->cmd[0], 0);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		g_data->cmd_paths++;
	}
	ft_error_exit(3);
	return (NULL);
}
