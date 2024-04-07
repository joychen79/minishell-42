# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 15:34:37 by rrimonte          #+#    #+#              #
#    Updated: 2024/03/17 15:10:16 by rrimonte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	libft.a
HEADERS		= 	libft.h
SRCS		=	ft_bzero.c \
				ft_strlen.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_split.c \
				ft_split_extra.c \
				ft_split_limit.c \
				ft_strlcpy.c \
				ft_strjoin.c \
				ft_strncmp.c \
				ft_strchr.c \
				ft_isalnum.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_putstr_fd.c \
				ft_strdup.c

OBJS		= 	${SRCS:.c=.o}
CC			= 	gcc
AR			= 	ar rcs
CFLAGS		= 	-Wall -Wextra -Werror
CFLAGS2		= 	-Wall -Wextra -Werror #-g3 -fsanitize=address
RM			= 	rm -rf


all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus
