/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2023/11/26 18:40:50 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

char	*var_name(char	*argv)
{
	char	*name;
	int		i;

	i = 0;

	if (!argv)
		return (NULL);
	name = NULL;
	while (argv[i])
	{
		if (argv[i] == '=')
		{
			name = ft_substr(argv, (int)0, i);
		}
		i++;
	}
	return (name);
	free(name);
}

int	is_existing(t_env *env, char *name)
{
	int		exist_len;
	int		new_len;

	if (!env || name == NULL)
		return (-1);
	exist_len = ft_strlen(var_name(env->value));
	new_len = ft_strlen(name);
	while (env)
	{
		if ((exist_len > new_len)
			&& (!(ft_strncmp(var_name(env->value), name, exist_len))))
			return (1);
		if ((exist_len < new_len)
			&& (!(ft_strncmp(var_name(env->value), name, new_len))))
			return (1);
		env = env->next;
	}
	return (0);
}
void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}
static void		free_node( t_env *env)
{
	if ( env->next == NULL)
	{
		ft_memdel(env->value);
		env->value = NULL;
		env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

//igual hay problema a la hora de borrar la linea de env!!!

void	unset(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;

	while (env && env->next)
	{
		name = var_name(env->value);
		if (!(strcmp(var_name(env->next->value), argv)))
		{
			aux = env->next->next;
			free_node(env->next);
			env->next = aux;
		}
		env = env->next;
	}
}

int	main(int ac, char **argv, char **env)
{
	t_env	*envp;
	//char	*name;
	//int		i;
	if (ac > 1)
	{
		envp = get_env(env);
		//name = var_name(argv[1]);
		/*printf("%s\n", name);
		i = is_existing(envp, name);
		if (i == 0)
			ft_printf("is new variation\n");
		else if(i == 1)
			ft_printf("it´s existing variation\n");
		else
			{
				ft_printf("invalid variation\n");
			return(0);
			}*/
		
		if (!(strncmp("myunset", argv[1], ft_strlen(argv[1]))))
		unset (envp, argv[2]);
		while (envp)
		{
			printf("%s\n", envp->value);
			envp = envp->next;	
		}
	}
	return (0);
}
