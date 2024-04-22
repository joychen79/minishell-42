/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:00:05 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/22 07:01:38 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// Función  para dividir una cadena en comandos y flags

void	leaks(void)
{
	system("leaks -q minishell");
}

char	*count_quotes(t_data *g_data, char *end)
{
	const char	delimiters[] = "<|>";

	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->bcomillas == 1
			|| g_data->cmd_lst->bcomillas2 == 1))
	{
		g_data->cmd_lst->bcomillas = 0;
		g_data->cmd_lst->bcomillas2 = 0;
	}
	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->infile_tag == 1
			|| g_data->cmd_lst->infile_tag == 2
			|| g_data->cmd_lst->outfile_tag == 1
			|| g_data->cmd_lst->outfile_tag == 2))
	{
		while (*end != '\0' && (ft_strchr(" ", *end) == NULL
				&& ft_strchr(delimiters, *end) == NULL))
		{
			if (*end == '"')
				check_marks(g_data, 0);
			if (*end == '\'')
				check_marks(g_data, 1);
			end++;
		}
		while ((*end != '\0' && ft_strchr(delimiters, *end) == NULL
				&& ft_strchr(" ", *end) == NULL)
			|| (g_data->cmd_lst->bcomillas == 1
				|| g_data->cmd_lst->bcomillas2 == 1))
		{
			g_data->bspaces++;
			if (*end != ' ' && ft_strchr(delimiters, *end) == NULL)
				g_data->bspaces = 0;
			if (*end == '"')
				check_marks(g_data, 0);
			if (*end == '\'')
				check_marks(g_data, 1);
			end++;
			if (*end != '\0' && ft_strchr(delimiters, *end) != NULL
				&& ft_strchr(" ", *end) != NULL
				&& (g_data->cmd_lst->bcomillas == 1
					|| g_data->cmd_lst->bcomillas2 == 1))
				end++;
		}
	}
	else
	{
		while (*end != '\0' && ft_strchr(delimiters, *end) == NULL)
		{
			g_data->bspaces++;
			if (*end != ' ' && ft_strchr(delimiters, *end) == NULL)
				g_data->bspaces = 0;
			if (*end == '"')
				check_marks(g_data, 0);
			if (*end == '\'')
				check_marks(g_data, 1);
			end++;
			if (*end != '\0' && ft_strchr(delimiters, *end) != NULL
				&& (g_data->cmd_lst->bcomillas == 1
					|| g_data->cmd_lst->bcomillas2 == 1))
				end++;
		}
	}
	return (end);
}

void	splitcommands(char *input, t_data *g_data, t_env	*envp)
{
	char	*start;
	char	*end;

	start = input;
	end = 0;
	ft_init_var(g_data);
	ft_check_semicolon(start, g_data, envp);
	start = input;
	while (*start != '\0')
	{
		inicialize_list(g_data);
		start = skip_delimiters(start, g_data, envp);
		end = start;
		g_data->bspaces = 0;
		end = count_quotes(g_data, end);
		check_tag(g_data, end);
		ft_catch_cmd(g_data, end, start, envp);
		start = check_if_pipe(g_data, start, end);
	}
	ft_order(g_data, envp);
	ft_backward_node(g_data);
	while (g_data->cmd_lst && g_data->cmd_lst->next != 0)
		g_data->cmd_lst = g_data->cmd_lst->next;
	ft_backward_node(g_data);
}

char	*ft_erase_quotes(t_data *g_data, int i, int j, int quotes)
{
	char	*tmp;
	
	g_data->cmd_lst->bcomillas = 0;
	g_data->cmd_lst->bcomillas2 = 0;
	while (g_data->cmd_lst->cmdaux[i])
	{
		if (g_data->cmd_lst->cmdaux[i] == '"'
			&& g_data->cmd_lst->bcomillas2 == 0)
		{
			check_marks(g_data, 0);
			quotes++;
		}
		if (g_data->cmd_lst->cmdaux[i] == '\''
			&& g_data->cmd_lst->bcomillas == 0)
		{
			check_marks(g_data, 1);
			quotes++;
		}
		i++;
	}
	tmp = (char *)malloc (sizeof(char) * (i - quotes + 1));
	i = 0;
	while (g_data->cmd_lst->cmdaux[i])
	{
		if (g_data->cmd_lst->cmdaux[i] == '"')
			check_marks(g_data, 0);
		if (g_data->cmd_lst->cmdaux[i] == '\'')
			check_marks(g_data, 1);
		if (g_data->cmd_lst->cmdaux[i] == '"'
			&& g_data->cmd_lst->bcomillas2 == 1)
		{
			check_marks(g_data, 0);
			tmp[j] = g_data->cmd_lst->cmdaux[i];
			j++;
		}
		if (g_data->cmd_lst->cmdaux[i] == '\''
			&& g_data->cmd_lst->bcomillas == 1)
		{
			printf("|%c|\n",g_data->cmd_lst->cmdaux[i]);
			check_marks(g_data, 1);
			tmp[j] = g_data->cmd_lst->cmdaux[i];
			j++;
		}
		if(g_data->cmd_lst->cmdaux[i] != '"'
			&& g_data->cmd_lst->cmdaux[i] != '\'')
		{
			tmp[j] = g_data->cmd_lst->cmdaux[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_count_builtins(t_data *g_data, t_env *envp)
{
	int		i;
	int		x;
	int		z;
	int		j;
	int		len;
	int		lenaux;
	int		lenaux2;
	int		lentotal;
	char	*tmp;
	char	*cmdtemp;
	int		position;

	i = 0;
	position = 0;
	x = 0;
	z = 0;
	j = 0;
	len = 0;
	lenaux = 0;
	lenaux2 = 0;
	lentotal = 0;
	tmp = NULL;
	len = ft_strlen(g_data->cmd_lst->cmdaux);
	while (len > i)
	{
		lenaux2 = 0;
		if (g_data->cmd_lst->cmdaux[i] == '"')
			check_marks(g_data, 0);
		if (g_data->cmd_lst->cmdaux[i] == '\'')
			check_marks(g_data, 1);
		if (g_data->cmd_lst->cmdaux[i] == '$' 
			&& g_data->cmd_lst->bcomillas2 == 0)
		{
			position = i;
			if (g_data->cmd_lst->cmdaux[i + 1])
			{
				if (g_data->cmd_lst->cmdaux[i + 1] == '?')
				{
					lenaux2 = 2;
					tmp = var_expansion("$?", envp);
					lenaux = ft_strlen(tmp);
					i++;
				}
			}
			if (lenaux2 == 0)
			{
				i++;
				lenaux2++;
				while (g_data->cmd_lst->cmdaux[i]
					&& ft_isalnum(g_data->cmd_lst->cmdaux[i]) == 1)
				{
					lenaux2++;
					i++;
				}
				i = position;
				cmdtemp = (char *)malloc (sizeof(char) * lenaux2 + 1);
				z = 0;
				cmdtemp[z] = g_data->cmd_lst->cmdaux[i];
				i++;
				z++;
				while (g_data->cmd_lst->cmdaux[i]
					&& ft_isalnum(g_data->cmd_lst->cmdaux[i]) == 1)
				{
					cmdtemp[z] = g_data->cmd_lst->cmdaux[i];
					i++;
					z++;
				}
				cmdtemp[z] = '\0';
				tmp = var_expansion(cmdtemp, envp);
				free (cmdtemp);
				if (tmp != NULL)
					lenaux = ft_strlen(tmp);
				else
					lenaux = 0;
			}
			lentotal = lenaux - lenaux2;
			cmdtemp = (char *)malloc (sizeof(char) * len + lentotal + 1);
			x = 0;
			z = 0;
			j = 0;
			while (len > x)
			{
				if (x == position)
				{
					x = x + lenaux2;
					if (tmp != NULL)
					{
						while (tmp[j])
						{
							cmdtemp[z] = tmp[j];
							z++;
							j++;
						}
					}
					if (len + lentotal == z)
						z--;
				}
				if (g_data->cmd_lst->cmdaux[x])
					cmdtemp[z] = g_data->cmd_lst->cmdaux[x];
				z++;
				x++;
			}
			cmdtemp[z] = '\0';
			free(g_data->cmd_lst->cmdaux);
			len = ft_strlen(cmdtemp);
			g_data->cmd_lst->cmdaux = (char *)malloc (sizeof(char) * len + 1);
			z = 0;
			while (cmdtemp[z])
			{
				g_data->cmd_lst->cmdaux[z] = cmdtemp[z];
				z++;
			}
			g_data->cmd_lst->cmdaux[z] = '\0';
			free(tmp);
			free(cmdtemp);
			i = -1;
		}
		i++;
	}
	tmp = ft_erase_quotes(g_data, 0, 0, 0);
	free(g_data->cmd_lst->cmdaux);
	g_data->cmd_lst->cmdaux = tmp;
	if (g_data->cmd_lst->infile_tag == 0 && g_data->cmd_lst->outfile_tag == 0)
		g_data->cmd_lst->cmd = ft_split_limit(g_data->cmd_lst->cmdaux, ' ');
	i = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data		*g_data;
	t_env		*envp;

	//atexit(leaks);
	if (argc != 1)
	{
		perror("error, don't add parameters");
		exit(1);
	}
	(void)argv;
	g_data = malloc(sizeof(t_data));
	if (g_data == NULL)
		return (0);
	ft_init_main(g_data, env);
	envp = NULL;
	envp = get_env(env);
	increment_shlv(envp);
	ft_actualize_env(g_data, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_loop_input(g_data, envp);
	return (0);
}
