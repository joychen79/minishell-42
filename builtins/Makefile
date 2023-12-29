# so_long
NAME	=	buildins

SRC		=	echo.c \
			env.c \
			export.c \
			get_env.c \
			pwd.c
#			main.c

OBJS				= $(SRC:.c=.o)

# Libft
LIBFT				=	libft.a
LIBFT_SRC			=	../libft/

# Compiler
CC					=	cc
RM					=	rm -f
CFLAGS				=	-g3 -fsanitize=address #-Wall -Werror -Wextra


# Rules
all:		$(LIBFT) $(NAME)

$(LIBFT):
			@make -C $(LIBFT_SRC)
			
$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_SRC)$(LIBFT) -o $(NAME)

clean:
			@make -C libft fclean
			@$(RM) $(OBJS)


fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
