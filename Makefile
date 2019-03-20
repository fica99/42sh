# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/20 21:09:08 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

ECHO=echo

CD=cd

SRC=
 
INCLUDES=includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all: cd echo $(NAME)

$(NAME):
			@make re -C $(LIB)
			@gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft
echo :
			@make re -C $(LIB)
			@gcc $(EXTRA_FLAGS) -o $(ECHO) srcs/echo/main.c srcs/echo/echo.c -I libft/includes -I $(INCLUDES) -L $(LIB) -lft
cd:
			@make re -C $(LIB)
			@gcc $(EXTRA_FLAGS) -o $(CD) srcs/cd/main.c srcs/cd/cd.c -I libft/includes -I $(INCLUDES) -L $(LIB) -lft			
clean:
			@make clean -C $(LIB)

fclean: clean
			@make fclean -C $(LIB)
			@rm -f $(NAME)
			@rm -f $(ECHO)
			@rm -f $(CD)
re: fclean all