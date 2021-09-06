# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/14 16:22:58 by ogenser           #+#    #+#              #
#    Updated: 2021/08/19 15:53:35 by ogenser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

SRCS:= $(filter-out ft_lst%.c, $(wildcard *.c))

all : $(NAME)

$(NAME) :	$(OBJS)
			ar rcs $(NAME) $^

$(OBJS) : $(HEADERS)

%.o: %.c
			$(CC) $(FLAGS) -c $< -o $@

bonus :
			$(CC) $(FLAGS) -c ft_lst*.c
			ar rcs $(NAME) ft_lst*.o

clean :
			rm -f *.o

fclean : clean
			rm -f  $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
