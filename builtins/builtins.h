/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:06:27 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/16 20:18:51 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		exit_stat;
	char	**env;
	char	*pwd;
}	t_shell;

/* Global Function */
int	g_exit_status;

/* BuiltIn Functions */
int		ft_pwd(void);
int		ft_echo(char **args);
//int		ft_env(char **env);
int		ft_env(t_env *env);
t_env	*get_env(char **str);
t_env	*new_env(char *str);
void	addenv_back(t_env **env, t_env *new);
int		env_size(t_env *env);
void	ft_unset(t_env **env, char	*argv);
int		ft_export(t_env *env, char	*argv);
int		is_existing(t_env **env, char *name);
char	*var_name(char	*argv);
char	*get_current_path(t_env *env);
int		ft_cd(char *args, t_env *env);
char	*path_option(char *argv, t_env *env);
void	exec_builtin(char **args, t_env *env);
int		is_builtin(char *command);

/*Manage Expansions*/
char	*var_expansion(char *argv, t_env *env);
char	*parsing_doller(char *argv);
char	*envvalue(char *env);
char	*parsing_g_exit_state(char *argv);
void	echo_expansion(char **argv, t_env *env);

#endif