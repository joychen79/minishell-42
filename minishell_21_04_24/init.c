/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:32:44 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/20 12:40:47 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_main(t_data *g_data, char **env)
{
	g_data->b_env = 0;
	if (env[0] == NULL)
		g_data->b_env = 1;
	g_data->env_p = NULL;
	g_data->cmd_lst = NULL;
	g_data->bcontinue = 0;
	g_data->bexit = 0;
}

void	ft_init_var(t_data *g_data)
{
	g_data->bsection = 0;
	g_data->cmd_count = 0;
	g_data->total_count = 0;
	g_data->bclose = 0;
	g_data->border = 0;
	g_data->borderaux = 0;
	g_data->infl = -1;
	g_data->outfl = -1;
	g_data->cmd_rute = 0;
	g_data->b_append = 0;
	g_data->herecount = 0;
	g_data->status = 0;
}

t_env	*ft_loop_input_2(t_data *g_data, t_env *envp)
{
	int			inputlen;
	int			i;
	int			bstart;

	bstart = 0;
	add_history(g_data->input);
	inputlen = ft_strlen(g_data->input);
	if (g_data->input[0] != '\0')
	{
		i = 0;
		while (i < inputlen)
		{
			if (g_data->input[i] != ' ' && g_data->input[i] != '\t')
				bstart = 1;
			i++;
		}
		if (bstart == 1)
		{
			g_data->bsection = 0;
			splitcommands(g_data->input, g_data, envp);
			envp = pipex(g_data, envp);
		}
		free(g_data->input);
	}
	return (envp);
}

void	ft_loop_input(t_data *g_data, t_env *envp)
{
	while (g_data->bexit == 0)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		g_data->in_std = dup(STDIN_FILENO);
		g_data->input = readline("Ingresa tu mensaje: ");
		if (g_data->input == NULL)
		{
			ft_free_end(g_data, envp);
			exit(0);
		}
		if (ft_strncmp(g_data->input, "clear", 5) == 0)
		{
			printf("\033[2J\033[H");
			free(g_data->input);
		}
		else
			envp = ft_loop_input_2(g_data, envp);
	}
	if (g_data->bexit == 1)
	{
		ft_free_end(g_data, envp);
		exit(0);
	}
}

void	ft_catch_cmd(t_data *g_data, char *end, char *start, t_env	*envp)
{
	if (*start != '\0')
	{
		g_data->cmd_lst->cmdaux = (char *)malloc (sizeof(char)
				* ((end - g_data->bspaces) - start + 1));
		ft_strlcpy(g_data->cmd_lst->cmdaux, start,
			(end - g_data->bspaces) - start + 1);
		ft_check_quotes(g_data, envp);
		g_data->cmd_lst->s_tg = g_data->bsection;
		if (g_data->cmd_lst->infile_tag == 0
			&& g_data->cmd_lst->outfile_tag == 0)
			g_data->cmd_count++;
		g_data->total_count++;
	}
}
