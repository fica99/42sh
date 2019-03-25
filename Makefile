# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/25 21:56:47 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

ECHO=echo

ECHO_SRCS=builtins/echo/echo.c
CD=cd

CD_SRCS=builtins/cd/cd.c
ENV=env

ENV_SRCS=builtins/env/env.c

SETENV=setenv

SETENV_SRCS=builtins/setenv/setenv.c

UNSETENV=unsetenv

UNSETENV_SRCS=builtins/unsetenv/unsetenv.c

SRCS=srcs/get.c\
	srcs/flags.c\
	srcs/make.c\
	srcs/print.c\
	srcs/parse.c\
	srcs/shell.c\
	srcs/check.c
 
INCLUDES=includes

INCLUDES_LIB=libft/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all:$(NAME) $(CD) $(ECHO) $(ENV) $(SETENV) $(UNSETENV)

$(NAME):
			mkdir bin
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft

$(ECHO) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(ECHO) $(SRCS) $(ECHO_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(ECHO) ./bin/echo

$(CD):
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(CD) $(SRCS) $(CD_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft			
			mv $(CD) ./bin/cd

$(ENV) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(ENV) $(SRCS) $(ENV_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(ENV) ./bin/env

$(SETENV) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(SETENV) $(SRCS) $(SETENV_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(SETENV) ./bin/setenv

$(UNSETENV) :
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(UNSETENV) $(SRCS) $(UNSETENV_SRCS) -I $(INCLUDES_LIB) -I $(INCLUDES) -L $(LIB) -lft
			mv $(UNSETENV) ./bin/unsetenv
clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)
			rm -rf ./bin/
			
re: fclean all