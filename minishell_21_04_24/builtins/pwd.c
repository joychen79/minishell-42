/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:01 by jingchen          #+#    #+#             */
/*   Updated: 2024/04/03 17:13:26 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"
//extern int	g_exit_status;

int	ft_pwd(void)
{
	char	buf[1024];
	char	*cwd;

	cwd = getcwd(buf, sizeof(buf));
	if (cwd == NULL)
	{
		perror("Can not get current working directory!\n");
		g_exit_status = 1;
		return (1);
	}
	else
		printf("%s\n", buf);
	return (0);
}
