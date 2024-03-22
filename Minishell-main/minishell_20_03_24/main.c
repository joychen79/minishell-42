/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:00:05 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/22 17:49:53 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// Función  para dividir una cadena en comandos y flags
void	leaks(void)
{
	system("leaks -q minishell");
}

void	splitcommands(const char *input, t_data *g_data, t_env	*envp)
{
	const char	delimiters[] = "<|>";
	const char	*start;
	const char	*end;
	int			bcomillas;
	int			bcomillas2;
	int			bspaces;
	int			i;
	int			count;
	int			count2;
	int			ntokens;

	count = 0;
	count2 = 0;
	start = input;
	end = 0;
	bcomillas = 0;
	bcomillas2 = 0;
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
	while (*start != '\0')
	{
		ntokens = 0;
		i = 0;
		inicialize_list(g_data);
		// Saltar los delimitadores iniciales
		while (*start != '\0' && ft_strchr(delimiters, *start) != NULL)
		{
			if (*start == '|' )
			{
				if (g_data->cmd_lst->infile_tag == 1 || ntokens > 0
					|| g_data->cmd_lst->outfile_tag == 1)
				{
					//cambiar a mensaje de error
					printf("syntax error near unexpected token `|'\n");
					exit(1);
				}
				ntokens++;
			}
			if (*start == '"')
			{
				if (bcomillas == 0)
					bcomillas = 1;
				else
					bcomillas = 0;
			}
			if (*start == '\'')
			{
				if (bcomillas2 == 0)
					bcomillas2 = 1;
				else
					bcomillas2 = 0;
			}
			if (*start == '<' && (bcomillas == 0 || bcomillas2 == 0))
			{
				if (g_data->cmd_lst->infile_tag == 1
					|| g_data->cmd_lst->outfile_tag == 1)
				{
					//cambiar a mensaje de error
					printf("syntax error near unexpected token `<'\n");
					exit(1);
				}
				g_data->cmd_lst->infile_tag = 1;
				start++;
				if (*start == '<')
				{
					g_data->cmd_lst->infile_tag = 2;
					g_data->herecount++;
					start++;
				}
				start--;
			}
			if (*start == '>' && (bcomillas == 0 || bcomillas2 == 0))
			{
				if (g_data->cmd_lst->infile_tag == 1
					|| g_data->cmd_lst->outfile_tag == 1)
				{
					//cambiar a mensaje de error
					printf("syntax error near unexpected token `>'\n");
					exit(1);
				}
				g_data->cmd_lst->outfile_tag = 1;
				start++;
				if (*start == '>')
				{
					g_data->cmd_lst->outfile_tag = 2;
					start++;
				}
				start--;
			}
			if (*start == '\\' && (bcomillas == 0 || bcomillas2 == 0))
			{
				start++;
				if (ft_strchr(delimiters, *start) == NULL)
					g_data->cmd_lst->bjoin = 0;
				else
					g_data->cmd_lst->bjoin = 1;
			}
			if (*start != '\0')
				start++;
			while (*start == ' ')
				start++;
		}
		while (*start == ' ')
			start++;
		// Encontrar el final del comando
		end = start;
		bspaces = 0;
		if (g_data->cmd_lst != NULL && (g_data->cmd_lst->infile_tag == 1
				|| g_data->cmd_lst->infile_tag == 2
				|| g_data->cmd_lst->outfile_tag == 1))
		{
			while (*end != '\0' && ft_strchr(" ", *end) == NULL)
				end++;
		}
		else
		{
			while (*end != '\0' && ft_strchr(delimiters, *end) == NULL)
			{
				bspaces++;
				if (*end != ' ' && ft_strchr(delimiters, *end) == NULL)
					bspaces = 0;
				if (*end == '"')
				{
					if (bcomillas == 0)
						bcomillas = 1;
					else
						bcomillas = 0;
				}
				if (*end == '\'')
				{
					if (bcomillas2 == 0)
						bcomillas2 = 1;
					else
						bcomillas2 = 0;
				}
				end++;
				if (*end != '\0' && ft_strchr(delimiters, *end) != NULL
					&& (bcomillas == 1 || bcomillas2))
					end++;
			}
			if (*end == '|')
				g_data->cmd_lst->tag = 2;
			else if (*end == '>')
			{
				end++;
				if (*end == '>')
					g_data->cmd_lst->tag = 3;
				else
					g_data->cmd_lst->tag = 4;
				end--;
			}
		}
		// Construye el comando completo incluyendo flags
		if (*start != '\0')
		{
			g_data->cmd_lst->cmdaux = (char *)malloc (sizeof(char)
					* ((end - bspaces) - start + 1));
			ft_strlcpy(g_data->cmd_lst->cmdaux, start,
				(end - bspaces) - start + 1);
			printf("cmdaux-->|%s|\n", g_data->cmd_lst->cmdaux);
			printf("infile_tag--->|%d|\n", g_data->cmd_lst->infile_tag);
			printf("outfile_tag-->|%d|\n", g_data->cmd_lst->outfile_tag);
			//Comprobar si tiene comillas abiertas cada comando
			while (g_data->cmd_lst->cmdaux[i])
			{
				if (g_data->cmd_lst->cmdaux[i] == '"')
					count++;
				if (g_data->cmd_lst->cmdaux[i] == '\'')
				{
					g_data->cmd_lst->bvar = 1;
					count2++;
				}
				i++;
			}
			if (count % 2 != 0 || count2 % 2 != 0)
			{
				//cambiar a codigo de error
				printf("error comillas abiertas\n");
				exit(1);
			}
			if (g_data->cmd_lst->previous == 0 && ntokens != 0)
			{
				//cambiar a codigo de error
				printf("**syntax error near unexpected token `|'\n");
				exit(1);
			}
			g_data->cmd_lst->s_tg = g_data->bsection;
			if (g_data->cmd_lst->infile_tag == 0
				&& g_data->cmd_lst->outfile_tag == 0)
				g_data->cmd_count++;
			g_data->total_count++;
		}
		start = end;
		while (*start == ' ')
			start++;
		if (ft_strchr(delimiters, *start) != NULL)
		{
			if (*start == '|')
			{
				g_data->cmd_lst->tag = 2;
				g_data->bsection++;
			}
		}
	}
	ft_order(g_data, envp);
	ft_backward_node(g_data);
	pipex(g_data, envp);
}

static void	ft_count_builtins(t_data *g_data, t_env *envp)
{
	int		i;
	char	*tmp;

	i = 0;
	if (g_data->cmd_lst->infile_tag == 0 && g_data->cmd_lst->outfile_tag == 0)
	{
		g_data->cmd_lst->cmd = ft_split_limit(g_data->cmd_lst->cmdaux, ' ');
		while (g_data->cmd_lst->cmd[i] && g_data->cmd_lst->bvar == 0)
		{
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

void	ft_order(t_data *g_data, t_env *envp)
{
	if (g_data->cmd_lst == NULL)
	{
		printf("syntax error near unexpected token `;'\n");
		exit(1);
	}
	if (g_data->cmd_lst->cmdaux == NULL)
	{
		//cambiar el printf por perror y ponerlo donde el main_bonus
		if (g_data->cmd_lst->infile_tag == 1)
			printf("syntax error near unexpected token `<'\n");
		else if (g_data->cmd_lst->outfile_tag == 1)
			printf("syntax error near unexpected token `>'\n");
		else
			printf("syntax error near unexpected token `|'\n");
		exit(1);
	}
	while (g_data->border == 0)
	{
		ft_backward_node(g_data);
		ft_forward_node(g_data);
	}
	ft_backward_node(g_data);
	while (g_data->cmd_lst != 0 && g_data->cmd_lst->next != 0)
	{
		ft_count_builtins(g_data, envp);
		g_data->cmd_lst = g_data->cmd_lst->next;
	}
	ft_count_builtins(g_data, envp);
}

int	main(int argc, char **argv, char **env)
{
	t_data		*g_data;
	int			inputlen;
	int			i;
	int			bstart;
	t_env		*envp;

	//atexit(leaks);
	if (argc != 1)
	{
		perror("error, no añadas parametros");
		exit(1);
	}
	(void)argv;
	envp = NULL;
	inputlen = 0;
	g_data = malloc(sizeof(t_data));
	if (g_data == NULL)
		return (0);
	g_data->b_env = 0;
	if (env[0] == NULL)
		g_data->b_env = 1;
	envp = get_env(env);
	g_data->env_p = NULL;
	ft_actualize_env(g_data, envp);
	g_data->cmd_lst = NULL;
	g_data->bcontinue = 0;
	g_data->bexit = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (g_data->bexit == 0)
	{
		g_data->in_std = dup(STDIN_FILENO);
		bstart = 0;
		g_data->input = readline("Ingresa tu mensaje: ");
		if (g_data->input == NULL)
		{
			printf("Error al leer la entrada\n");
			ft_free_end(g_data, envp);
			return (1);
		}
		if (ft_strncmp(g_data->input, "clear", 5) == 0)
		{
			printf("\033[2J\033[H");
			free(g_data->input);
		}
		else
		{
			add_history(g_data->input);
			inputlen = ft_strlen(g_data->input);
			printf("g_exit_status es--->|%d|\n", g_exit_status);
			printf("input---->|%s|\n", g_data->input);
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
				}
				printf("libero input\n");
				free(g_data->input);
			}
		}
	}
	printf("Fin del main...\n");
	ft_free_end(g_data, envp);
	return (0);
}
/*
si quito el enviroment, export tiene que funcionar, y al usar env, mostrarme solo lo que acabo de exportar
tengo que hacer split de los infile y outfile para quitar comillas



*/