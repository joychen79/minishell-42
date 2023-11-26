/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:06:27 by jingchen          #+#    #+#             */
/*   Updated: 2023/11/26 18:24:14 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

int		ft_pwd(void);
int		ft_echo(char **args);
int		ft_env(char **env);
//char **get_env(char **env);
t_env	*get_env(char **str);
t_env	*new_env(char *str);
void	addenv_back(t_env **env, t_env *new);
int		env_size(t_env *env);
void	unset(t_env *env, char	*name);

#endif