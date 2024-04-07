/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:02:11 by rrimonte          #+#    #+#             */
/*   Updated: 2024/03/31 13:39:42 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_data *g_data, t_env	*envp)
{
	ft_check_files(g_data, envp);
	g_data->i = 0;
	ft_backward_node(g_data);
	printf("antes de pipes\n");
	create_pipes(g_data, envp);
	ft_free_all(g_data);
}

void	ft_error_exit(int err)
{
	if (err == 0)
		perror("incorrect number of argument");
	else if (err == 2)
		perror("incorrect outfile");
	else if (err == 3)
		perror("command not found");
	else if (err == 4)
		perror("failed to execute");
	exit(1);
}

void	ft_error(int err, t_data *g_data, t_env *envp)
{
	if (err == 0)
		perror("found forbiden char `;'");
	else if (err == 1)
		perror("syntax error near unexpected token `|'");
	else if (err == 2)
		perror("syntax error near unexpected token `<'");
	else if (err == 3)
		perror("syntax error near unexpected token `>'");
	else if (err == 4)
		perror("found forbiden char `quotes'");
	ft_free_error(g_data, err);
	ft_loop_input(g_data, envp);
}
