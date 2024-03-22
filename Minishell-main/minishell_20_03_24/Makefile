# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrimonte <rrimonte@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:50:55 by rrimonte          #+#    #+#              #
#    Updated: 2024/03/19 01:38:41 by rrimonte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
LIBS_TARGET		:= 	libft/libft.a
HEADERS			=	pipex_bonus/pipex_bonus.h
SRCS			=	get_next_line/get_next_line_bonus.c \
					get_next_line/get_next_line_utils_bonus.c \
					pipex_bonus/ft_organize.c \
					pipex_bonus/ft_files_bonus.c \
					pipex_bonus/ft_lst_bonus.c \
					pipex_bonus/ft_pipes_bonus.c \
					free.c \
					pipex_bonus/main_bonus.c \
					builtins/env.c \
					builtins/echo.c \
					builtins/unset.c \
					builtins/get_env.c \
					builtins/pwd.c \
					builtins/cd.c \
					builtins/export.c \
					builtins/exe_builtins.c \
					builtins/var_expansion.c \
					main.c \
					builtins/signal.c \
					utils.c
					
					

OBJS			=	$(SRCS:.c=.o)
CC				=	gcc
GET_NEXT_LINE_FOLDER	=	get_next_line/
LIBFT_FOLDER	=	libft/
LIBFT_NAME		=	libft.a
LIBS			=	$(LIBFT_FOLDER)$(LIBFT_NAME)
AR				=	ar rcs
CFLAGS			=	-Wall -Wextra -Werror #-g -fsanitize=address #-O3 
RM				=	rm -rf
RLINE_FLG_R42 =-L/Users/rrimonte/.brew/Cellar/readline/8.1.2/lib
RLINE_INC_R42 =-I/Users/rrimonte/.brew/Cellar/readline/8.1.2/include


$(NAME): $(LIBS) $(OBJS) $(HEADERS)
		$(CC)  $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -lreadline
$(LIBS_TARGET):
	$(MAKE) -C $(LIBFT_FOLDER)
all: $(NAME)
clean:
	$(MAKE) -C $(LIBFT_FOLDER) clean
	$(RM) $(OBJS)
fclean: clean
	$(MAKE) -C $(LIBFT_FOLDER) fclean
	$(RM) $(NAME)
re: fclean all
