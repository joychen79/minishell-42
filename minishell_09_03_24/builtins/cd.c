/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/18 20:04:07 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
//extern	int	g_exit_status;
// step 1: save the current working directory in a char *;
// step 2: use chdir to change working directory;
// step 3: save the new directory in a char * and update the PWD in the env;
// step 4: use the previous directory to apdate the OLDPWD in the env;

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

/*char	*path_option(char *argv, t_env *env)
{
	char	*path;
	char	*varname;

	while (env)
	{
		varname = var_name(env->value);
		if (!argv)
		{
			if (!ft_strncmp (varname, "HOME", ft_strlen(varname)))
				path = envvalue(env->value);
		}
		else if (ft_strncmp(argv, "-", ft_strlen(argv)) == 0)
		{
			if (!ft_strncmp(varname, "OLDPWD", ft_strlen(varname)))
				path = envvalue(env->value);
		}
		env = env->next;
		free(varname);
	}
	return (path);
}*/

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

/*int	ft_cd(char *argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*aux;
	int		code;

	aux = get_current_path(env);
	oldpwd = ft_strjoin("OLDPWD=", aux, 0);
	if (!argv || ft_strncmp (argv, "-", ft_strlen (argv)) == 0)
	{
		free(aux);
		aux = path_option (argv, env);
		newpwd = ft_strjoin("PWD=",aux, 0);
	}
	else
		newpwd = ft_strjoin("PWD=", argv, 0);
	if (!argv || ft_strncmp (argv, "-", ft_strlen (argv)) == 0)
	{
		free(aux);
		aux = path_option (argv, env);
		code = chdir (aux);
	}
	else
		code = chdir (argv);
	if (!code)
	{
		ft_export(env, oldpwd);
		ft_export(env, newpwd);
		g_exit_status = 0;
	}
	else (llevar a exit de errores)
	{
		printf ("cd: no such file or directory: %s\n", argv);
		g_exit_status = 1;
	}
	free(aux);
	free(oldpwd);
	free(newpwd);
	return (0);
}*/
