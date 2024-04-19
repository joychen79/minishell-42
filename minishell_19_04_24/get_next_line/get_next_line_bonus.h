/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:35:24 by rrimonte          #+#    #+#             */
/*   Updated: 2023/04/17 14:44:26 by rrimonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd, int mode);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strchr_get(const char *string, int searchedChar);
size_t	ft_strlcpy_get(char *dst, const char *src, size_t dstsize);
void	*ft_calloc_get(size_t elementCount, size_t elementSize);
size_t	ft_strlen_get(const char *theString);

typedef struct s_list
{
	struct s_list	*previous;
	struct s_list	*next;
	int				fd;
	char			*sbuff;
}					t_list;

t_list	*deletenod_get(t_list *buff);

#endif