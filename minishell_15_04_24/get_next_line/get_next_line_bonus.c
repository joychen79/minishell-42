/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:35:50 by rrimonte          #+#    #+#             */
/*   Updated: 2024/01/26 11:51:00 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*f_clean(char *str)
{
	char	*line;
	int		i;
	int		x;
	int		z;

	i = 0;
	x = 0;
	z = 0;
	while (str[i] && str[i] != '\n')
		i++;
	while (str[z] != '\0')
		z++;
	line = ft_calloc_get((z - i + 1), sizeof(char));
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
		line[x] = str[i];
		i++;
		x++;
	}
	free (str);
	return (line);
}

char	*f_line(char *str, int mode)
{
	char	*line;
	int		i;

	i = 0;
	if (str[i] == '\0')
	{
		free (str);
		return (0);
	}
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc_get((i + 2), sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str [i];
		i++;
	}
	if (mode == 1)
		line[i] = '\n';
	return (line);
}

char	*f_read(int fd, char *str)
{
	char	*auxbuff;
	int		n_read;
	int		n_bool;

	n_bool = 0;
	if (!str)
		str = ft_calloc_get(1, 1);
	auxbuff = malloc(BUFFER_SIZE + 1 * sizeof(char));
	n_read = 1;
	while (n_read > 0 && n_bool == 0)
	{
		n_read = read(fd, auxbuff, BUFFER_SIZE);
		if (n_read == -1)
		{
			free(auxbuff);
			return (0);
		}
		auxbuff[n_read] = '\0';
		str = ft_strjoin_get(str, auxbuff);
		if (ft_strchr_get(auxbuff, '\n'))
			n_bool = 1;
	}
	free(auxbuff);
	return (str);
}

t_list	*inlist(int fd, t_list *buff)
{
	t_list	*temp;

	while (buff != 0 && buff->previous != 0)
		buff = buff->previous;
	while (buff != 0 && buff->next != 0 && buff->fd != fd)
		buff = buff->next;
	if (!(buff != 0 && buff->fd == fd))
	{
		temp = (t_list *)malloc(sizeof(*buff));
		if (temp == 0)
			return (0);
		temp->fd = fd;
		temp->sbuff = 0;
		temp->next = 0;
		if (buff == 0)
			temp->previous = 0;
		else
		{
			buff->next = temp;
			temp->previous = buff;
		}
		buff = temp;
	}
	return (buff);
}

char	*get_next_line(int fd, int mode)
{
	char			*line;
	static t_list	*buff;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (0);
	buff = inlist(fd, buff);
	if (buff == 0)
		return (0);
	if (read(fd, 0, 0) < 0)
	{
		if (buff->sbuff != 0)
			free(buff->sbuff);
		buff = deletenod_get(buff);
		return (0);
	}
	buff->sbuff = f_read(fd, buff->sbuff);
	if (buff->sbuff == 0)
		return (0);
	line = f_line(buff->sbuff, mode);
	if (line != 0)
		buff->sbuff = f_clean(buff->sbuff);
	if (buff->sbuff == 0 || line == 0)
		buff = deletenod_get(buff);
	return (line);
}
