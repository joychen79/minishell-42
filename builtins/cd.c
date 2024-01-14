/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:28:16 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/14 16:48:16 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		if (ft_strncmp(varname,
				"PWD", ft_strlen (varname))== 0)
		{
				curr_path = envvalue (env->value);	
		}
		env = env->next;	
	}
	return (curr_path);
}

/*char *go_to_path(int option, t_env *env)
{
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = var_expansion("HOME", env);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return ("ERROR");
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return ("ERROR");
		update_oldpwd(env);
	}
	return (env_path);
}*/

char *path_option(char *argv, t_env *env)
{
	char	*path;
	char *varname;

	while(env)
	{
		varname = var_name(env->value);
		if(!argv)
		{
			if(!ft_strncmp(varname, "HOME", ft_strlen(varname)))
				path = envvalue(env->value);
				break;
		}
		else if(ft_strncmp(argv, "-", ft_strlen(argv)) == 0)
		{
			if(!ft_strncmp(varname,"OLDPWD", ft_strlen(varname)))
				path = envvalue(env->value);
				break;
		}
	env = env->next;
	}
	return(path);
}

int	ft_cd(char **args, t_env *env)
{
	char	*oldpwd;
	char	*newpwd;

	/*if (!args[1])
	{
		oldpwd = ft_strjoin("OLDPWD=", get_current_path(env));
		newpwd = ft_strjoin("PWD=", path_option(args[1],env));
	}*/
	if (!args[1]||ft_strncmp(args[1], "-", ft_strlen(args[1]))== 0)
	{
		oldpwd = ft_strjoin("OLDPWD=", get_current_path(env));
		newpwd = ft_strjoin("PWD=", path_option(args[1],env));
	}

	else
	{
		oldpwd = ft_strjoin("OLDPWD=", get_current_path(env));
		newpwd = ft_strjoin("PWD=", args[1]);
	}
	ft_export(env, oldpwd);
	chdir(args[1]);
	ft_export(env, newpwd);
	//free(oldpwd);
	//free(newpwd);
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_env *envp;
	envp = get_env(env);
	char *curren;
	char *old;
/*	curren = get_current_path(envp);
	printf("my current : %s\n", curren);*/
	//update_oldpwd(envp);
	ft_cd(av, envp);
	while(envp)
	{
		printf("%s\n", envp->value);
		envp = envp->next;
	}

	return 0;
}
/*char *update_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", get_current_path(env));
	return(oldpwd);
}

char *update_newpwd(char *argv,t_env *env)
{
	char	*newpwd;

	newpwd = ft_strjoin("PWD=", argv);
	return (newpwd);
}*/



/*static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return ("ERROR");
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return ("ERROR");
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}*/