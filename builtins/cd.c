/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/20 18:04:12 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// se debe gesitar 

char	*get_current_path(t_env *env)
{
	char	*curr_path;
	char	*varname;

	while (env)
	{
		varname = var_name(env->value);
		if (ft_strncmp (varname,
				"PWD", ft_strlen (varname)) == 0)
		{
			curr_path = envvalue (env->value);
		}
		env = env->next;
	}
	return (curr_path);
}

char	*path_option(char *argv, t_env *env)
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
	}
	return (path);
}

int	ft_cd(char *argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	int		code;

	oldpwd = ft_strjoin("OLDPWD=", get_current_path(env));
	if (!argv || ft_strncmp (argv, "-", ft_strlen (argv)) == 0)
		newpwd = ft_strjoin("PWD=", path_option(argv, env));
	else
		newpwd = ft_strjoin("PWD=", argv);
	if (!argv || ft_strncmp (argv, "-", ft_strlen (argv)) == 0)
		code = chdir (path_option (argv, env));
	else
		code = chdir(argv);
	if (!code)
	{
		ft_export(env, oldpwd);
		ft_export(env, newpwd);
		g_exit_status = 0;
	}
	else
	{
		ft_printf ("cd: no such file or directory: %s\n", argv);
		exit (1);
	}
		return (0);
}

/*int main (int ac, char **av, char **env)
{
	t_env	*envp;
	envp = get_env(env);
	char *curren;
	char *old;
	curren = get_current_path(envp);
	printf("my current : %s\n", curren);
	//update_oldpwd(envp);
	ft_cd(av[1], envp);
//printf("%s\n", path_option(av[1], envp));
	while(envp)
	{
		printf("%s\n", envp->value);
		envp = envp->next;
	}

	return 0;
}*/