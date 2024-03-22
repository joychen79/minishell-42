/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:03:58 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/22 00:59:08 by rrimonte         ###   ########.fr       */
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
}	t_data;

void	inicialize_list(t_data *g_data);
void	ft_order(t_data *g_data, t_env *envp);
void	ft_backward_node(t_data *g_data);
void	ft_forward_node(t_data *g_data);
void	pipex(t_data *g_data, t_env	*envp);
void	ft_actualize_env(t_data *g_data, t_env	*envp);
void	ft_free_end(t_data *g_data, t_env	*envp);
char	*var_expansion(char *argv, t_env *env);

#endif