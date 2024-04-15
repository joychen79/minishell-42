/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:18:47 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/13 13:17:41 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_check_files(t_data *g_data, t_env	*envp)
{
	if (envp != NULL)
	{
		g_data->b_env = 0;
		if (envp == NULL)
			g_data->b_env = 1;
		if (g_data->b_env == 0)
		{
			while (envp != NULL && ft_strncmp("PATH", envp->value, 4))
				envp = envp->next;
			if (envp == NULL)
			{
				g_data->b_env = 1;
				return ;
			}
			if (ft_strncmp("", (envp->value + 5), 1) != 0)
			{
				g_data->paths = envp->value + 5;
				g_data->cmd_paths = ft_split(g_data->paths, ':');
			}
		}
	}
}

/**
 * The function creates a temporary file and reads input from the user until a
 * specific string is entered, writing the input to the file.
 */


void	ft_here_doc_file(t_data *g_data)
{
	signal(SIGINT, quite_heredoc);
	ft_here_doc_2(g_data);
	exit (0);
}

void	ft_here_doc_2(t_data *g_data)
{
	char	*temp;

	close(g_data->cmd_lst->fd[READ_O]);
	write(1, "pipe heredoc> ", 14);
	temp = get_next_line(0, 1);
	if (temp == NULL)
	{
		free(temp);
		printf("\n");
		exit(0);
	}
	if (ft_strncmp(g_data->cmd_lst->cmdaux, temp,
			ft_strlen(g_data->cmd_lst->cmdaux) + 1) != 0)
	{
		write (g_data->cmd_lst->fd[WRITE_O], temp, ft_strlen(temp));
	}
	while (ft_strncmp(g_data->cmd_lst->cmdaux, temp,
			ft_strlen(g_data->cmd_lst->cmdaux) + 1) != 0)
	{
		free(temp);
		write(1, "pipe heredoc> ", 14);
		temp = get_next_line(0, 1);
		if (temp == NULL)
		{
			free(temp);
			printf("\n");
			exit(0);
		}
		if (ft_strncmp(g_data->cmd_lst->cmdaux, temp,
				ft_strlen(g_data->cmd_lst->cmdaux) + 1) != 0)
		{
			write (g_data->cmd_lst->fd[WRITE_O], temp, ft_strlen(temp));
		}
	}
	close(g_data->cmd_lst->fd[WRITE_O]);
	free(temp);
}
