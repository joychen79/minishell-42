/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:41:02 by jingchen          #+#    #+#             */
/*   Updated: 2024/03/21 23:24:08 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_rl_replace_line(const char *text)
{
	printf("\033[2K\033[0G");
	printf("%s", text);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf ("\n");
		rl_on_new_line();
		ft_rl_replace_line("");
		rl_redisplay ();
		g_exit_status = 1;
	}
}
