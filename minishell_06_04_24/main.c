/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:00:05 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/07 15:45:09 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// Función  para dividir una cadena en comandos y flags
/*
void	leaks(void)
{
	system("leaks -q minishell");
}*/

char	*count_quotes(t_data *g_data, char *end)
{
	const char	delimiters[] = "<|>";

	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->infile_tag == 1
			|| g_data->cmd_lst->infile_tag == 2
			|| g_data->cmd_lst->outfile_tag == 1))
	{
		while (*end != '\0' && ft_strchr(" ", *end) == NULL)
			end++;
	}
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
				|| g_data->cmd_lst->bcomillas2))
			end++;
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
}

char	*ft_erase_quotes(t_data *g_data, int i, int j, int quotes)
{
	char	*tmp;

	while (g_data->cmd_lst->cmdaux[i])
	{
		if (g_data->cmd_lst->cmdaux[i] == '"'
			|| g_data->cmd_lst->cmdaux[i] == '\'')
			quotes++;
		i++;
	}
	tmp = (char *)malloc (sizeof(char) * (i - quotes + 1));
	i = 0;
	while (g_data->cmd_lst->cmdaux[i])
	{
		if (g_data->cmd_lst->cmdaux[i] != '"'
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
	char	*tmp;

	i = 0;
	tmp = ft_erase_quotes(g_data, 0, 0, 0);
	free(g_data->cmd_lst->cmdaux);
	g_data->cmd_lst->cmdaux = tmp;
	if (g_data->cmd_lst->infile_tag == 0 && g_data->cmd_lst->outfile_tag == 0)
	{
		g_data->cmd_lst->cmd = ft_split_limit(g_data->cmd_lst->cmdaux, ' ');
		if (g_data->cmd_lst->cmd[0] != NULL)
		{
			while (g_data->cmd_lst->cmd[i] && g_data->cmd_lst->bvar == 0)
			{
				printf("|||||%s\n", envp->value);
				tmp = var_expansion(g_data->cmd_lst->cmd[i], envp);
				if (tmp != NULL)
				{
					free(g_data->cmd_lst->cmd[i]);
					g_data->cmd_lst->cmd[i] = tmp;
				}
				i++;
			}
		}
	}
}


int	main(int argc, char **argv, char **env)
{
	t_data		*g_data;
	t_env		*envp;

	//atexit(leaks);
	if (argc != 1)
	{
		perror("error, no añadas parametros");
		exit(1);
	}
	(void)argv;
	g_data = malloc(sizeof(t_data));
	if (g_data == NULL)
		return (0);
	ft_init_main(g_data, env);
	envp = NULL;
	//if(*env != NULL)
		envp = get_env(env);
	//increment_shlv(envp);
	envp = ft_actualize_env(g_data, envp);
	printf("<<<<<<<<<<%s\n", envp->value);

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_loop_input(g_data, envp);
	printf("Fin del main...\n");
	return (0);
}
/*
tengo que hacer split de los infile y outfile para quitar comillas

He quitado esto
	//	if (g_data->cmd_lst != NULL && (g_data->cmd_lst->infile_tag == 1
		//		|| g_data->cmd_lst->infile_tag == 2
		//		|| g_data->cmd_lst->outfile_tag == 1))
		//{
			while (*end != '\0' && ft_strchr(" ", *end) == NULL)
				end++;
		//}
		//else
	//	{
			end = count_quotes(g_data, end);
			check_tag(g_data, end);
	//	}
*/