/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:41:02 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/18 20:02:39 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

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
	signal(SIGINT, SIG_DEF);
	signal(SIGQUIT, SIG_DEF);*/

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf ("\n"); 
		rl_on_new_line();
		//rl_replace_line("", 0); 
		rl_redisplay (); 
		g_exit_status = 1; 
	}
}


/*void	sig_int(int code, t_sig g_sig)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", STDERR);
		ft_putstr_fd("\n", STDERR);
		//ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
		g_exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		g_exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code, t_sig g_sig)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	free (nbr);
}

void	sig_init(void)
{
	t_sig	g_sig;

	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_exit_status = 0;
}*/


