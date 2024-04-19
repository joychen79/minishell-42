/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/19 18:34:55 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_old_path(t_env *env)
{
	char	*curr_path;
	char	*varname;
	char	*oldpwd;

	while (env)
	{
		varname = var_name(env->value);
		if (ft_strncmp (varname,
				"PWD", ft_strlen (varname)) == 0)
			curr_path = envvalue (env->value);
		env = env->next;
		free(varname);
	}
	oldpwd = ft_strjoin("OLDPWD=", curr_path, 0);
	free (curr_path);
	return (oldpwd);
}

char	*get_new_path(void)
{
	char	buf[1024];
	char	*cwd;
	char	*newpwd;

	cwd = getcwd(buf, sizeof(buf));
	if (cwd == NULL)
	{
		printf("cd: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
		newpwd = "NULL";
	}
	newpwd = ft_strjoin("PWD=", cwd, 0);
	return (newpwd);
}

static int	cd_error(char *argv)
{
	printf ("cd: %s: no such file or directory\n", argv);
	return (1);
}

t_env	*ft_cd(char *argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	int		code;

	newpwd = NULL;
	if (!env)
		return (NULL);
	oldpwd = get_old_path(env);
	code = chdir (argv);
	if (!code)
	{
		newpwd = get_new_path();
		if (newpwd == NULL)
		{
			return (env);
		}
		env = ft_export(env, oldpwd);
		env = ft_export(env, newpwd);
	}
	else
		cd_error(argv);
	free(oldpwd);
	free(newpwd);
	return (env);
}
