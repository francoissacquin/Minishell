# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ogenser <ogenser@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 15:59:12 by ogenser           #+#    #+#              #
#    Updated: 2021/09/06 11:55:25 by ogenser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minishell

TESTER = tester

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g  -fsanitize=address -g3

SFLAGS = -lreadline

HEADER = inc/minishell.h

SRC = srcs/main.c \
srcs/parser/parse.c \
srcs/utils.c \
srcs/builtins/cd.c \
srcs/builtins/echo.c \
srcs/builtins/env.c \
srcs/builtins/exit.c \
srcs/builtins/export.c \
srcs/builtins/pwd.c \
srcs/builtins/unset.c \

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): ${OBJ}
	@echo "\n\033[0;32mCompiling libft\033[0m"
	cd libft && make
	@echo "\n\033[0;32mCompiling\033[0m"
	# $(CC) ${LIBFT} ${CFLAGS} $(OBJ) -o $(NAME)
	$(CC) ${CFLAGS} ${SFLAGS} $(OBJ) ${LIBFT} -o $(NAME)
	@echo "\n\033[0;32mDONE\033[0m"

tester:
	gcc -Wall -Wextra -Werror libft/libft.a -fsanitize=address -g tester.c -o tester

clean:
	@echo "\033[0;31mWipeout..."
	cd libft && make fclean
	rm -rf $(OBJ)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	rm -f tester
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
