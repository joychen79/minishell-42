/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:03:58 by rrimonte          #+#    #+#             */
/*   Updated: 2024/04/06 21:55:24 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define RUTE "/usr/bin/whereis"
# define WRITE_O 1
# define READ_O 0
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line_bonus.h"
# include "../minishell.h"
# include "../builtins/builtins.h"
# include <errno.h>
# include <signal.h>

void		inicialize_list(t_data *g_data);
void		ft_join(t_data *g_data);
void		ft_init_here_docs(t_data *g_data);
void		ft_order_outfiles(t_data *g_data);
void		ft_order_infiles(t_data *g_data);
void		find_rute(t_data *g_data);
void		ft_check_infiles(t_data *g_data);
int			exec_builtins_father(t_data *g_data, t_env *envp);
int			exec_exit_father(t_data *g_data);
void		create_pipes(t_data *g_data, t_env	*envp);
void		create_pipes_end(t_data *g_data, int *pid, int child_pid);
int			create_pipes1(t_data *g_data, t_env *envp);
void		create_pipes2(t_data *g_data);
int			*create_pipes3(t_data *g_data, t_env *envp, int *pid);
int			*new_pipe(t_data *g_data, int *pid);
void		child(t_data *g_data, t_env	*envp);
void		ft_free_all(t_data *g_data);
void		ft_here_doc_file(t_data *g_data);
void		ft_here_doc_2(t_data *t_g_data);
void		ft_exit(t_data *g_data, int *pid, int child_pid);
void		ft_error(int err, t_data *g_data, t_env *envp);
void		ft_error_exit(int err);
void		ft_check_files(t_data *g_data, t_env	*envp);
char		*get_cmd_path(t_data *g_data);

#endif
