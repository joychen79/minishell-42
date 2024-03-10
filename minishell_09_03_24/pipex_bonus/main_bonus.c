/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:02:11 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/06 23:07:48 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pipex(t_data *g_data, t_env	*envp)
{
	ft_check_files(g_data, envp);
	g_data->i = 0;
	ft_backward_node(g_data);
	create_pipes(g_data, envp);
	printf("antes de liberar\n");
	ft_free_all(g_data);
	printf("despues de liberar\n");
	return (0);
}



void	ft_error(int err)
{
	if (err == 0)
	{
		perror("incorrect number of argument");
		exit(1);
	}
	if (err == 1)
		perror("incorrect infile");
	if (err == 2)
	{
		perror("incorrect outfile");
		exit(1);
	}
	if (err == 3)
	{
		perror("command not found");
		exit(1);
	}
	if (err == 4)
	{
		perror("failed to execute");
		exit(1);
	}
}
