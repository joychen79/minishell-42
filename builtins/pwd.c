/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:01 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/16 19:19:36 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int	ft_pwd(void)
{
	char	buf[1024];
	char	*cwd;

	cwd = getcwd(buf, sizeof(buf));
	if (cwd == NULL)
	{
		perror("Can not get current working directory!\n");
		g_exit_status = 1;
		exit(-1);
	}
	else
		ft_printf("%s\n", buf);
	g_exit_status = 0;
	return (0);
}
