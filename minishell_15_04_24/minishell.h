/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:03:58 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/11 00:36:48 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
# include "builtins/builtins.h"


typedef struct t_l_data
{
	struct t_l_data		*previous;
	struct t_l_data		*next;
	char				**cmd;
	char				*cmdaux;
	int					tag;
	int					bjoin;
	int					s_tg;
	int					infile_tag;
	int					outfile_tag;
	int					bexport;
	int					fd[2];
	int					bvar;
	int					berrorinf;
	int					bcomillas;
	int					bcomillas2;
}	t_data_list;

typedef struct t_g_data
{
	struct t_l_data		*cmd_lst;
	int					status;
	char				**env_p;
	char				*input;
	int					berror;
	int					in_std;
	int					infl;
	int					outfl;
	char				*here_doc;
	int					b_append;
	int					b_env;
	int					i;
	int					x;
	char				*paths;
	char				**cmd_paths;
	char				*cmd_rute;
	int					cmd_count;
	int					total_count;
	int					bclose;
	int					border;
	int					borderaux;
	int					bsection;
	int					bcontinue;
	int					bexit;
	int					herecount;
	int					bspaces;
}	t_data;

void	ft_init_main(t_data *g_data, char **env);
void	ft_loop_input(t_data *g_data, t_env *envp);
void	ft_init_var(t_data *g_data);
void	splitcommands(char *input, t_data *g_data, t_env	*envp);
void	ft_count_builtins(t_data *g_data, t_env *envp);
void	ft_order(t_data *g_data, t_env *envp);
void	inicialize_list(t_data *g_data);
void	ft_check_semicolon(char *start, t_data *g_data, t_env	*envp);
void	ft_check_quotes(t_data *g_data, t_env	*envp);
void	check_tag(t_data *g_data, char *end);
char	*check_if_pipe(t_data *g_data, char *start, char *end);
void	ft_catch_cmd(t_data *g_data, char *end, char *start, t_env	*envp);
void	ft_error(int err, t_data *g_data, t_env *envp);
void	ft_error_exit(int err);
char	*skip_delimiters(char *start, t_data *g_data, t_env *envp);
char	*skip_spaces(char *start);
void	check_marks(t_data *g_data, int option);
void	ft_order(t_data *g_data, t_env *envp);
void	ft_backward_node(t_data *g_data);
void	ft_forward_node(t_data *g_data);
void	pipex(t_data *g_data, t_env	*envp);
void	ft_actualize_env(t_data *g_data, t_env	*envp);
void	ft_free_end(t_data *g_data, t_env	*envp);
char	*var_expansion(char *argv, t_env *env);
void	ft_free_error(t_data *g_data, int error);

#endif