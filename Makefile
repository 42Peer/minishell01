NAME = minishell
CC = cc
#CCFLAGS	=	-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -g -lreadline
CCFLAGS		=	-Wall -Wextra -Werror
CCFLAGS_G	=	-Wall -Wextra -Werror -g
IREADLINE	=	-I /usr/local/opt/readline/include/
LREADLINE	=	-L /usr/local/opt/readline/lib/
RM	=	rm -f

SRCS	=	main.c \
			env_handler.c \
			tokenize.c \
			make_tree.c \
			tree_parser.c \
			quote.c \
			execute.c \
			signal_handler.c \
			test.c utils.c \
			builtin_pwd.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_unset.c
OBJS	=	$(SRCS:.c=.o)

ifdef	WITH_BONUS
	OBJECTS	=	$(OBJS_B)
else
	OBJECTS	=	$(OBJS)
endif

all	:	$(NAME)

bonus	:
	make WITH_BONUS=1 all

.c.o	:
	$(CC) $(CCFLAGS) $(IREADLINE) -c -o $@ $<

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) $(LREADLINE) -lreadline -o $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

lldb: all
	$(CC) $(OBJS) $(CCFLAGS_G) $(LREADLINE) -lreadline -o $(NAME)

re	:	fclean all

.PHONY	:	all bonus clean fclean re
