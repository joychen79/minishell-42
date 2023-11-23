/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:19:22 by jingchen          #+#    #+#             */
/*   Updated: 2023/11/23 19:24:35 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

char **get_env(char **env)
{
	char	**aux;
	int		i;
	int		j;
	int		size;
	int		l_size;
	int		k;
	
	size = 0;
	while (env[size])
		size ++;
	if (!(aux = (char **)malloc((sizeof (char *) * (size + 1)))))
		return (NULL);
	j = 0;
	while(env[j])
	{
		l_size = 0;
		while(env[j][l_size])
			l_size++;
		if(!(aux[j]=(char *)malloc(sizeof(char) * (l_size + 1))))
			return(NULL);
		i = 0;
		k =0;
		while(l_size)
			{
				aux[j][i++] = env[j][k++];
				l_size--;
			}
		aux[j][i] = '\0';
		j++;
	}
	return(aux);
}

int	ft_env(char **env)
{
	char **aux = get_env(env);
	int	i;
	i = -1;
	while (aux[++i])
	{
		ft_printf("%s\n", aux[i]);
	}
	return (0);
}
