/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:01 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 16:02:14 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

extern	int	g_exit_status;

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
		printf("%s\n", buf);
	g_exit_status = 0;
	return (0);
}
