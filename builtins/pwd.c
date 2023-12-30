/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:11:01 by jingchen          #+#    #+#             */
/*   Updated: 2023/12/30 13:38:02 by jingchen         ###   ########.fr       */
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
		exit (-1);
	}
	else
		ft_printf("Current working directory is: %s\n", buf);
	return (0);
}
