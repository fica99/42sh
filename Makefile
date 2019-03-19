# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/19 21:46:30 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRC=srcs/echo.c\
	srcs/cd.c\
	srcs/env.c\
	srcs/check.c\

INCLUDES=includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all: $(NAME)

$(NAME):
			@make re -C $(LIB)
			@gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft

clean:
			@make clean -C $(LIB)

fclean: clean
			@make fclean -C $(LIB)
			@rm -f $(NAME)

re: fclean all