# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: filip <filip@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/04/21 23:56:09 by filip            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=srcs/make.c\
	srcs/check.c\
	srcs/print.c\
	srcs/ft_errno.c\
	srcs/shell.c\
	srcs/signal.c\
	srcs/reading.c\
	srcs/make2.c\
	srcs/make3.c\
	srcs/parse.c\
	srcs/make4.c\
	srcs/autocom.c\

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
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRCS) $(BUILTINS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft

clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)

re: fclean all