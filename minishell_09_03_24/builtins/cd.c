/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/24 14:13:03 by jingchen         ###   ########.fr       */
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
	return (oldpwd);
}

char	*get_new_path(void)
{
	char	buf[1024];
	char	*cwd;
	char	*newpwd;

	cwd = getcwd(buf, sizeof(buf));
	newpwd = ft_strjoin("PWD=", cwd, 0);
	return (newpwd);
}

static int	cd_error(char *argv)
{
	printf ("cd: no such file or directory: %s\n", argv);
	return (1);
}

int	ft_cd(char *argv, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;
	int		code;

	newpwd = NULL;
	printf("eooo!!!!!!!!!!!!!!!!!!!!!!\n");
	if (!env)
		return (1);
	oldpwd = get_old_path(env);
	code = chdir (argv);
	if (!code)
	{
		printf("iiiii!!!!!!!!!!!!!!!!!!!!!!\n");
		newpwd = get_new_path();
		ft_export(env, oldpwd);
		printf("iiiii!!!!!!!!!!!!!!!!!!!!!!\n");
		ft_export(env, newpwd);
		printf("iiiii!!!!!!!!!!!!!!!!!!!!!!\n");
	}
	else
		cd_error(argv);
	free(oldpwd);
	free(newpwd);
	printf("eooo<<<<<<<<<<!!!!!!!!!!!!!!!!!!!!!!\n");
	return (0);
}
