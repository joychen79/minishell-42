/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:16:59 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/20 00:25:05 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

extern	int	g_exit_status;

void	ft_init_here_docs(t_data *g_data)
{
	int	*pid;
	int	child_pid;

	pid = NULL;
	child_pid = 0;
	if(g_data->herecount != 0)
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
			if (g_data->cmd_lst->infile_tag == 2 && pid[g_data->x] == 0)
			{
				ft_here_doc_file(g_data);
				g_data->x++;
			}
			else
			{
				if(g_data->cmd_lst->infile_tag == 2)
				{
					child_pid = waitpid(pid[g_data->x], &g_data->status, 0);
					if (child_pid == -1)
					{
						perror("Error al esperar here_doc");
						exit(EXIT_FAILURE);
					}
					if(g_data->status == 2)
						return ;
				}
				
				g_data->i++;
				if(g_data->cmd_lst->next != NULL)
					g_data->cmd_lst = g_data->cmd_lst->next;
			}
		}
		free(pid);
	}
}

void	ft_check_infiles(t_data *g_data)
{
	while (g_data->cmd_lst->infile_tag == 1)
	{
		g_data->infl = open(g_data->cmd_lst->cmdaux, O_RDONLY);
		if (g_data->infl < 0)
		{
			g_data->cmd_lst->berrorinf = 1;
			ft_error(1);
		}
		dup2(g_data->infl, STDIN_FILENO);
		close(g_data->infl);
		g_data->total_count--;
		if (g_data->cmd_lst->next != 0)
			g_data->cmd_lst = g_data->cmd_lst->next;
		else
		{
			g_data->cmd_lst->infile_tag = 3;
			g_data->total_count--;
		}
	}
	
}

void	create_pipes(t_data *g_data, t_env	*envp)
{
	int	*pid;
	int	child_pid;

	if(g_data->cmd_count != 0)
	{
		pid = (int *)malloc (sizeof(int) * g_data->cmd_count);
		if (pid == NULL)
			exit(0);
	}
	child_pid = 0;
	ft_init_here_docs(g_data);
	ft_backward_node(g_data);
	if(g_data->status == 2)
		return ;
	g_data->i = 0;
	while (g_data->i <= g_data->total_count - 1)
	{
		ft_check_infiles(g_data);
		if(g_data->cmd_count == 1 && g_data->cmd_lst->infile_tag == 0
			&& g_data->cmd_lst->outfile_tag == 0)
		{
			
			if (g_data->cmd_lst->cmd != NULL && ft_strncmp(g_data->cmd_lst->cmd[0]
				, "exit", ft_strlen(g_data->cmd_lst->cmd[0]) + 1) == 0)
			{
				g_data->bexit = 1;
				if (g_data->cmd_lst->cmd[1] != NULL)
				{
					if (g_data->cmd_lst->cmd[2] != NULL)
						perror("demasiados argumentos\n");
					else
						g_exit_status = ft_atoi(g_data->cmd_lst->cmd[1]);
				}
				break ;
			}
			if (g_data->cmd_lst->cmd != NULL &&
			(ft_strncmp(g_data->cmd_lst->cmd[0], "export", ft_strlen(g_data->cmd_lst->cmd[0])+ 1) == 0 ||
			ft_strncmp(g_data->cmd_lst->cmd[0], "unset", ft_strlen(g_data->cmd_lst->cmd[0])+ 1) == 0 ||
			ft_strncmp(g_data->cmd_lst->cmd[0], "cd", ft_strlen(g_data->cmd_lst->cmd[0])+ 1) == 0))
			{
				exec_builtin(g_data->cmd_lst->cmd, envp);
				ft_actualize_env(g_data, envp);
				g_data->total_count--;
				g_data->cmd_count--;
				g_data->cmd_lst->infile_tag = 4;
				if (g_data->cmd_lst->next != 0)
					g_data->cmd_lst = g_data->cmd_lst->next;
				else
					break;
			}
		}
		while ((g_data->cmd_lst->outfile_tag == 1 || g_data->cmd_lst->outfile_tag == 2) && g_data->total_count > 0)
		{
			if (g_data->cmd_lst->outfile_tag == 2)
				g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_CREAT | O_RDWR | O_APPEND, 0664);
			else
				g_data->outfl = open(g_data->cmd_lst->cmdaux,
					O_TRUNC | O_RDWR | O_CREAT, 0664);
			g_data->total_count--;
			if(g_data->cmd_lst->next != 0)
				g_data->cmd_lst = g_data->cmd_lst->next;
		}
		if(g_data->cmd_lst->infile_tag == 2)
		{
			g_data->total_count = g_data->total_count - 1;
			if (g_data->cmd_lst->next != 0)
				g_data->cmd_lst = g_data->cmd_lst->next;
		}
		if (g_data->cmd_lst->infile_tag == 0
			&& g_data->cmd_lst->outfile_tag == 0
			&& g_data->i <= g_data->total_count - 1
			&& g_data->cmd_lst->bexport == 0)
		{
			pipe(g_data->cmd_lst->fd);
			pid[g_data->i] = fork();
		}
		if (g_data->cmd_lst->infile_tag == 0
			&& g_data->cmd_lst->outfile_tag == 0
			&& g_data->i <= g_data->total_count - 1 
			&& pid[g_data->i] == 0 && g_data->cmd_lst->bexport == 0)
			child(g_data, envp);
		else
		{
			if(g_data->cmd_lst->previous != NULL && g_data->cmd_lst->previous->infile_tag == 2)
				close(g_data->cmd_lst->previous->fd[WRITE_O]);
			close(g_data->cmd_lst->fd[WRITE_O]);
			if (g_data->i < g_data->total_count - 1 && g_data->cmd_lst->next != 0)
				g_data->cmd_lst = g_data->cmd_lst->next;
			if (g_data->cmd_lst->outfile_tag == 1
				|| g_data->cmd_lst->outfile_tag == 2)
				g_data->total_count = g_data->total_count - 1;
			g_data->i++;
		}
	}
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
			if (child_pid == -1)
			{
				perror("Error al esperar al proceso hijo");
				exit(EXIT_FAILURE);
			}
			// Obtener el valor de salida del hijo
			g_exit_status = (g_data->status >> 8) & 0xFF;
			printf("valor obtenido->g_exit_status es--->|%d|\n",g_exit_status);
			g_data->i++;
		}
	}
	else
		ft_exit(g_data, pid, child_pid);
	if(g_data->cmd_count != 0)
		free(pid);
}

void	child(t_data *g_data, t_env	*envp)
{
	t_data_list	*aux;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	if (g_data->cmd_lst->next == 0)
	{
		exec_builtin(g_data->cmd_lst->cmd, envp);
		g_data->cmd_rute = get_cmd_path(g_data);
		printf("ruta----->|%s|\n",g_data->cmd_rute);
		execve(g_data->cmd_rute, g_data->cmd_lst->cmd, g_data->env_p);
		ft_error(4);
	}
	else if (g_data->cmd_lst->next != 0
		&& (g_data->cmd_lst->next->outfile_tag == 1
			|| g_data->cmd_lst->next->outfile_tag == 2))
	{
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
				ft_error(2);
			dup2(g_data->outfl, STDOUT_FILENO);
			close(g_data->outfl);
		}
		g_data->total_count--;
		g_data->cmd_lst = aux;
	}
	else
	{
		close (g_data->cmd_lst->fd[READ_O]);
		dup2(g_data->cmd_lst->fd[WRITE_O], STDOUT_FILENO);
		close (g_data->cmd_lst->fd[WRITE_O]);
	}
	if (g_data->cmd_lst->berrorinf == 1)
		exit(0);
	exec_builtin(g_data->cmd_lst->cmd, envp);
	g_data->cmd_rute = get_cmd_path(g_data);
	execve(g_data->cmd_rute, g_data->cmd_lst->cmd, g_data->env_p);
	ft_error(4);
}

char	*get_cmd_path(t_data *g_data)
{
	char	*tmp;
	char	*command;

	if (g_data->cmd_lst->cmd == 0)
		ft_error(3);
	if (access(g_data->cmd_lst->cmd[0], X_OK) == 0)
		return (g_data->cmd_lst->cmd[0]);
	else if (g_data->b_env == 1)
		ft_error(3);
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
	ft_error(3);
	return (NULL);
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
			perror("Error al esperar al proceso hijo en ft_exit");
			exit(EXIT_FAILURE);
		}
		x++;
		g_data->total_count--;
	}
	return ;
}
