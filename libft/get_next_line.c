/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:34:08 by jingchen          #+#    #+#             */
/*   Updated: 2023/07/10 17:05:56 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_buffer(char *old, char *new)
{
	char	*temp;

	temp = ft_strjoin(old, new);
	free(old);
	return (temp);
}

char	*read_line(int fd, char *buffer)
{
	char		*temp;
	int			readbyts;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (NULL);
	readbyts = 5;
	while (!ft_strchr(buffer, '\n') && readbyts != 0)
	{
		readbyts = read(fd, temp, BUFFER_SIZE);
		temp[readbyts] = '\0';
		buffer = join_buffer(buffer, temp);
	}
	free(temp);
	return (buffer);
}

char	*get_newline(char *buffer)
{
	char	*sub;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
	{
		i++;
	}
	sub = ft_calloc(i + 2, sizeof(char));
	while (i >= 0)
	{
		sub[i] = buffer[i];
		i--;
	}
	return (sub);
}

char	*get_newbuffer(char *buffer)
{
	int		i;
	char	*temp;
	char	*newbuffer;

	temp = ft_strchr(buffer, '\n');
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	temp++;
	newbuffer = ft_calloc(ft_strlen(temp) + 1, sizeof(char));
	i = 0;
	while (i <= (int)ft_strlen(newbuffer))
	{
		newbuffer[i] = temp[i];
		i++;
	}
	free(buffer);
	return (newbuffer);
}

char	*get_next_line(int fd)
{
	char		*newline;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	newline = get_newline(buffer);
	buffer = get_newbuffer(buffer);
	return (newline);
}
