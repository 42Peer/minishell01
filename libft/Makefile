# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 10:49:15 by sumsong           #+#    #+#              #
#    Updated: 2022/09/05 18:26:24 by jujeon           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
AR = ar
ARFLAGS = rcs

CC = gcc
CFLAGS = 

HEADER = libft.h
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			 ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			 ft_lstclear_bonus.c ft_lstiter_bonus.c \
			#  ft_lstmap_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME) $(BONUS_OBJS) $(HEADER)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)

$(NAME): $(OBJS) $(HEADER)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: all clean fclean re bonus
