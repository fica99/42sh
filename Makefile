# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/27 18:24:48 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=srcs/env_make.c\
	srcs/flags.c\
	srcs/make.c\
	srcs/print.c\
	srcs/parse.c\
	srcs/shell.c\
	srcs/check.c\
	srcs/autocom.c\
	srcs/ft_errno.c

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