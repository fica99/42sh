# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: filip <filip@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/26 11:01:33 by filip            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=srcs/get.c\
	srcs/flags.c\
	srcs/make.c\
	srcs/print.c\
	srcs/parse.c\
	srcs/shell.c\
	srcs/check.c

BUILTINS=builtins/cd/cd.c\
		builtins/echo/echo.c\
		builtins/env/env.c\
		builtins/setenv/setenv.c\
		builtins/unsetenv/unsetenv.c\

INCLUDES=includes

INCLUDES_LIB=libft/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all:$(NAME)

$(NAME):
			mkdir bin
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRCS) $(BUILTINS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft

clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)
			rm -rf ./bin/

re: fclean all