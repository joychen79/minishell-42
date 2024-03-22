/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/21 23:20:59 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
//extern	int	g_exit_status;

char	*get_current_path(t_env *env)
{
	char	*curr_path;
	char	*varname;

	while (env)
	{
		varname = var_name(env->value);
		if (ft_strncmp (varname,
				"PWD", ft_strlen (varname)) == 0)
			curr_path = envvalue (env->value);
		env = env->next;
		free(varname);
	}
	return (curr_path);
}

int	ft_cd(char *argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*aux;
	int		code;

	aux = get_current_path(env);
	oldpwd = ft_strjoin("OLDPWD=", aux, 0);
	newpwd = ft_strjoin("PWD=", argv, 0);
	code = chdir (argv);
	if (!code)
	{
		ft_export(env, oldpwd);
		ft_export(env, newpwd);
	}
	else //(llevar a exit de errores)
	{
		printf ("cd: no such file or directory: %s\n", argv);
		return (1);
	}
	free(aux);
	free(oldpwd);
	free(newpwd);
	return (0);
}
