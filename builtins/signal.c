/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:41:02 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/26 17:44:45 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf ("\n");
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay ();
		g_exit_status = 1;
	}
}

	
/*ctrl+c = SIGINT; ctrl+4 = SIGQUIT;

- en el proceso padre; (o sea main)
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n"); -> imprimir un salto de linea;
		rl_on_new_line(); -> inicial una linea nueva;
		rl_replace_line("", 0); -> replace un argumento vacio
		rl_redisplay(); -> redisplay lo de arriba;
		g_exit_status = 1; -> salida de commando sea error, con lo cual 1.
	}
}

- y si no hay readline = NULL, (recibe un ctrl+d is igual a ENDFILE,), llama la funcion de exit y cierra el minishell.

- el proceso hijo (o sea cuando gestionar heredoc o en modo bash)

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
