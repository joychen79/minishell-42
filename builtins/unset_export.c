/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:22:57 by jingchen          #+#    #+#             */
/*   Updated: 2023/12/30 14:14:26 by jingchen         ###   ########.fr       */
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
			break ;
		}
		i++;
	}
	if (argv[i] == '\0')
		name = ft_substr(argv, (int)0, i);
	return (name);
}

int	is_existing(t_env **env, char *name)
{
	int		exist_len;
	int		new_len;
	t_env	*aux;

	aux = *env;
	new_len = ft_strlen(name);
	if (!env || name == NULL)
		return (-1);
	while (aux)
	{
		exist_len = ft_strlen(var_name(aux->value));
		if ((exist_len == new_len)
			&& (!(ft_strncmp(var_name(aux->value), name, exist_len))))
		{
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}

void	unset(t_env **env, char *argv)
{
	t_env	*tmp;
	t_env	*aux;
	char	*name;

	if (!env || !*env)
		return ;
	while (*env && !(ft_strncmp(var_name((*env)->value), var_name(argv),
				ft_strlen(var_name((*env)->value)))))
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp);
	}
	aux = *env;
	while (aux && aux->next)
	{
		if (!(ft_strncmp(var_name(aux->next->value), var_name(argv),
					ft_strlen(var_name(aux->next->value)))))
		{
			tmp = aux->next;
			aux->next = tmp->next;
			free(tmp);
		}
		aux = aux->next;
	}
}

void	export(t_env *env, char	*argv)
{
	t_env	*aux;
	char	*name;

	name = var_name(argv);
	aux = new_env(argv);

	if (is_existing (&env, name) == 1)
	{
		unset (&env, name);
		addenv_back (&env, aux);
	}
	if (!is_existing(&env, name))
		addenv_back(&env, aux);
}

/*int	main(int ac, char **argv, char **env)
{
	t_env	*envp;
	char	*name;
	int		i;
	t_env	**aux_envp;


		envp = get_env(env);
		name = var_name(argv[1]);
		printf("%s\n", name);
		i = is_existing(&envp, name);
		if (i == 0)
			ft_printf("is new variation\n");
		else if(i == 1)
			ft_printf("it´s existing variation\n");
		else
			{
				ft_printf("invalid variation\n");
			return(0);
			}
	if (!(strncmp("myunset", argv[1], ft_strlen(argv[1]))))
		unset (&envp, argv[2]);
	if (!(strncmp("myexport", argv[1], ft_strlen(argv[1]))))
		export (envp, argv[2]);
	else if(!(ft_strncmp("myenv", argv[1], ft_strlen(argv[1]))))
			ft_env(env);
	while (envp)
		{
			printf("%s", (envp)->value);
			if(ft_strncmp(envp->value, "", ft_strlen((envp->value))))
				printf("\n");
			printf("node\n");
			envp = envp->next;	
		}

	return (0);
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

/*static void	free_env(t_env *env)
{
	if(env)
	{
	//free(env->value);
		free(env);
	env = NULL;
	}
}
*/