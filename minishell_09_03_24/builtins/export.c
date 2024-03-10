/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:56 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/10 15:59:02 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

/*int	ft_get_matrix_size(char **env)
{
	int	count;

	count = 0;
	while (*env)
	{
		count++;
		env++;
	}
	return (count);
}

char	**ft_sort_matrix(char **mat)
{
	int		i;
	int		j;
	int		len;
	char	*aux;

	i = 0;
	len = ft_get_matrix_size(mat);
	while (i < len)
	{
		j = -1;
		while (++j < (len - i - 1))
		{
			aux = mat[j];
			if (ft_strcmp(mat[j], mat[j + 1]) > 0)
			{
				aux = mat[j];
				mat[j] = mat[j + 1];
				mat[j + 1] = aux;
			}
		}
		i++;
	}
	return (mat);
}*/

t_env *sort_env(t_env *env)
{
	char	*aux;
	t_env	*tmp;
	int		i;

	tmp = env;
	while (env->next != NULL)
	{
		i = 0;
		while (env->value[i] && (env->value[i] == env->next->value[i]))
			i++;
		if (env->value[i] > env->next->value[i])
		{
			aux = env->value;
			env->value = env->next->value;
			env->next->value = aux;
		env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

void	print_export(t_env *env)
{
	int		i;
	t_env	*sorted;

	i = 0;
	sorted = sort_env(env);
	while (sorted)
	{
		printf("declare -x %s\n", sorted->value);
		sorted = sorted->next;
	}
		g_exit_status = 0;
	free(sorted);
}

int	ft_export(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;

	if (!argv)
		return (0);
	name = var_name(argv);
	aux = new_env(argv);
	if (is_existing (&env, name) == 1)
	{
		ft_unset (&env, name);
		addenv_back (&env, aux);
	}
	if (!is_existing(&env, name))
	{
		addenv_back(&env, aux);
	}
	g_exit_status = 0;
	free(name);
	return (0);
}

int	main(int ac, char **argv, char **env)
{
	t_env	*envp;
	char	*name;
	int		i;
	t_env	**aux_envp;


		envp = get_env(env);
		//name = var_name(argv[1]);
		//printf("%s\n", name);
		/*i = is_existing(&envp, name);
		if (i == 0)
			ft_printf("is new variation\n");
		else if(i == 1)
			ft_printf("it´s existing variation\n");
		else
			{
				ft_printf("invalid variation\n");
			return(0);
			}*/
	/*if (!(strncmp("myunset", argv[1], ft_strlen(argv[1]))))
		ft_unset (&envp, argv[2]);*/
	/*if (!(strncmp("myexport", argv[1], ft_strlen(argv[1]))))
		ft_export (envp, argv[2]);
	if (!(strncmp("myexport", argv[1], ft_strlen(argv[1]))) && !argv[2])
		print_export (envp);
	else if(!(ft_strncmp("myenv", argv[1], ft_strlen(argv[1]))))
			ft_env(envp);*/
	if (!(strncmp("myecho", argv[1], ft_strlen(argv[1]))))
		ft_echo (argv);
	/*while (envp)
		{
			printf("%s", (envp)->value);
			if(ft_strncmp(envp->value, "", ft_strlen((envp->value))))
				printf("\n");
			printf("node\n");
			envp = envp->next;	
		}*/

	return (0);
}
