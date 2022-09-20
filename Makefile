NAME = minishell
CC = cc
CCFLAGS	=	-g -lreadline
RM	=	rm -f

SRCS	=	quote.c main.c tokenize.c make_tree.c tree_parser.c test.c utils.c \
			env_handle.c
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
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME)	: $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $@

clean	:
	$(RM) $(OBJS_B) $(OBJS)

fclean	: clean
	$(RM) $(NAME) 

re	:	fclean all

.PHONY	:	all bonus clean fclean re