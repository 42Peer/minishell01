NAME = minishell
CC = cc
#CCFLAGS	=	-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -g -lreadline
CCFLAGS		=	-Wall -Wextra -Werror
IREADLINE	=	-I /usr/local/opt/readline/include/
LREADLINE	=	-L /usr/local/opt/readline/lib/
RM	=	rm -f

SRCS	=	quote.c main.c tokenize.c make_tree.c tree_parser.c test.c utils.c \
			env_handle.c signal_handle.c ft_pwd.c
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

re	:	fclean all

.PHONY	:	all bonus clean fclean re