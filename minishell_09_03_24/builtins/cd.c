/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/22 18:16:32 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*strrchr(const char *s, int c)
{
	int		i;
	//int		j;
	char	*new;

	i = 0;
	new = NULL;

	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			break ;
		i--;
	}
		
	/*j = 0;
	while (j < i)
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';*/
	new = ft_substr(s, 0, i);
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return (new);
}

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

char	*pars_argv(char *argv, t_env *env)
{
	char	*parsed;
	char	*name;
	char	*cur;

	parsed = NULL;
	cur = get_current_path(env);
	if (!env)
		return (NULL);
	if (!ft_strncmp (argv, "..", ft_strlen (argv)))
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		parsed = strrchr(cur, '/');
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");	
		
		printf(" parsed is : %s\n", parsed);
	}
	else if (!argv)
	{
		while (env)
		{
			name = var_name(env->value);
			if (!ft_strncmp (name, "HOME", ft_strlen (name)))
				parsed = envvalue(env->value);
			free(name);
		}
		env = env->next;
	}
	else
		parsed = argv;
		printf(" parsed is : %s\n", parsed);
	return (parsed);
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
	char	*aux;
	int		code;
	char	*parsed;

	parsed = pars_argv(argv, env);
	newpwd = NULL;
	oldpwd = NULL;
	if (!env)
		return (1);
	aux = get_current_path(env);
	code = chdir (parsed);
	if (!code)
	{
		oldpwd = ft_strjoin("OLDPWD=", aux, 0);
		newpwd = ft_strjoin("PWD=", parsed, 0);
		ft_export(env, oldpwd);
		ft_export(env, newpwd);
	}
	else
		cd_error(argv);
	free(aux);
	free(oldpwd);
	free(newpwd);
	return (0);
}
