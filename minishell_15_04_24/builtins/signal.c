/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:41:02 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/15 19:07:42 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_rl_replace_line(const char *text)
{
	printf ("\033[2K\033[0G");
	printf ("%s", text);
}

void	child_ctrl_c(int sig_num)
{
	(void)sig_num;
	ft_rl_replace_line("");
	write(1, "\n", 1);
	exit(0);
}

void	signal_handler(int sig)
{
	(void)sig;
	ft_rl_replace_line("");
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	quite_heredoc(int a)
{
	(void)a;
	exit(0);
}

void	signal_father(int sig)
{
	(void)sig;
	ft_rl_replace_line("");
	printf("\n");
	rl_on_new_line();
}
