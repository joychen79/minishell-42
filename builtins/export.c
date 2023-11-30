/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2023/11/30 20:19:27 by jingchen         ###   ########.fr       */
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
/*void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}*/

/*static void		free_node( t_env *env)
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
}*/

//igual hay problema a la hora de borrar la linea de env!!!

/*void	unset(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;
	//t_env	*tmp;

	if(!env)
		return ;

	while (env)
	{
		name = var_name(env->value);
		if (!(strncmp(name, argv, ft_strlen(name))))
		{
			aux = env->next;
			ft_memdel(env);
			env->next = aux;
		}
		env = env->next;
	}
}*/

static void	free_env(t_env *env)
{
	if(env)
	//free(env->value);
	{
		free(env);
	env = NULL;
	}
	
}

void	unset(t_env **env, char	*argv)
{
	t_env	*aux;
	t_env	*tmp;
	char	*name;
	if(!env || !*env)
		return ;
	tmp = *env;
	printf("1\n");
	while (tmp)
	{
		name = var_name(tmp->value);
		printf("name: %s\n", name);
		if (!(strncmp(name, argv, ft_strlen(name))))
		{
			aux = tmp->next;
			free_env(tmp);
			tmp->next = aux;
		}
		printf("2\n");
		tmp = tmp->next;
	}
}

void	export(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;
	name = var_name(env->value);
	aux = new_env(argv);
	
	if (is_existing(env, name) == 1)
		{
			unset(&env, name);
		addenv_back(&env, aux);
		}
	if (!is_existing(env, name))
		addenv_back(&env, aux);
}


/*int	main(int ac, char **argv, char **env)
{
	t_env	*envp;
	char	*name;
	int		i;
	t_env	*aux_envp;


		envp = get_env(env);
		//name = var_name(argv[2]);
		//printf("%s\n", name);
		i = is_existing(envp, name);
		if (i == 0)
			ft_printf("is new variation\n");
		else if(i == 1)
			ft_printf("it´s existing variation\n")
		else
			{
				ft_printf("invalid variation\n");
			return(0);
			}
	if (!(strncmp("myunset", argv[1], ft_strlen(argv[1]))))
		(unset (&envp, argv[2]), printf("llega\n"));
	if (!(strncmp("myexport", argv[1], ft_strlen(argv[1]))))
		export (envp, argv[2]);
	aux_envp = envp;
	while (aux_envp)
		{
			printf("%s\n", aux_envp->value);
			aux_envp =aux_envp->next;	
		}

		//printf("we are here");
	return (0);
}*/
