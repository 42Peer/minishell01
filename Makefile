NAME = minishell
CC 			=	cc
#CCFLAGS	=	-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -g -lreadline
CCFLAGS		=	-Wall -Wextra -Werror
CCFLAGS_G	=	-Wall -Wextra -Werror -g
SANITIZER	=	-fsanitize=address
IREADLINE	=	-I /usr/local/opt/readline/include/
LREADLINE	=	-L /usr/local/opt/readline/lib/
RM			=	rm -f

SRC_DIR		=	./srcs/
SRC			=	main.c \
				env_handler.c \
				tokenize.c \
				tokenize_utils.c tokenize_case1.c tokenize_case2.c \
				make_tree.c \
				make_tree_redir_node.c \
				tree_parser.c tree_parser_heredoc.c \
				execute.c \
				signal_handler.c \
				utils1.c utils2.c \
				utils_cleaners.c utils_system.c utils_list.c \
				utils_atoi.c utils_itoa.c utils_split.c utils_strjoin.c \
				cmd_action.c \
				delquote_expand.c delquote_utils.c \
				fork_frame.c \
				open_redir_file.c \
				path.c \
				test.c		# tmp file

BUILTIN_DIR	=	./builtin_srcs/
BUILTIN		=	builtin_pwd.c \
				builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export.c \
				builtin_unset.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC)) \
				$(addprefix $(BUILTIN_DIR), $(BUILTIN))
BUILTIN_SRCS=	$(addprefix $(BUILTIN_DIR), $(BUILTIN))
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

sani: $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) $(SANITIZER) $(LREADLINE) -lreadline -o $(NAME)

re	:	fclean all

.PHONY	:	all bonus clean fclean re