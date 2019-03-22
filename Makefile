# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/22 15:49:56 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

ECHO=echo

ECHO_SRCS=builtins/echo/main.c\
			builtins/echo/echo.c
CD=cd

CD_SRCS=builtins/cd/main.c\
		builtins/cd/cd.c
ENV=env

ENV_SRCS=builtins/env/main.c\
		builtins/env/env.c
LS=ls

LS_SRCS=builtins/ls

SRCS=srcs/get.c\
	srcs/flags.c
 
INCLUDES=includes

INCLUDES_LIB=libft/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all:$(NAME) $(CD) $(ECHO) $(LS) $(ENV)

$(NAME):
			mkdir bin
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(NAME) main.c  -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft

$(ECHO) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(ECHO) $(SRCS) $(ECHO_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(ECHO) ./bin/echo

$(CD):
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(CD) $(SRCS) $(CD_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft			
			mv $(CD) ./bin/cd

$(LS):
			make re -C $(LS_SRCS)
			mv $(LS_SRCS)/ft_ls ./bin/ls
			make fclean -C $(LS_SRCS)

$(ENV) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(ENV) $(SRCS) $(ENV_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(ENV) ./bin/env
	
clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)
			rm -rf ./bin/
			
re: fclean all