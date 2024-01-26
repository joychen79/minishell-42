# so_long
NAME	=	buildins

SRC		=	echo.c \
			env.c \
			unset_export.c \
			get_env.c \
			pwd.c \
			cd.c \
			exe_builtins.c \
			var_expansion.c \
			signal.c \
			main.c

OBJS				= $(SRC:.c=.o)

# Libft
LIBFT				=	libft.a
LIBFT_SRC			=	../libft/

# Compiler
CC					=	cc
RM					=	rm -f
CFLAGS				=	-g3 -fsanitize=address -Wall -Werror -Wextra

RL_LIB = -L /Users/$(USER)/.brew/opt/readline/lib
RL_INC = -I /Users/$(USER)/.brew/opt/readline/include

ifeq ($(UNAME), Linux)
RL_INC = -I/usr/local/include
RL_LIB = $(LIBFT) -L/usr/local/lib
endif

# Rules
all:		$(LIBFT) $(NAME)

$(LIBFT):
			@make -C $(LIBFT_SRC)
			
$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_SRC) $(LIBFT) -o $(NAME) $(RL_INC) $(RL_LIB) -lreadline

clean:
			@make -C $(LIBFT_SRC) fclean
			@$(RM) $(OBJS)


fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
