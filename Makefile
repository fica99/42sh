# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: filip <filip@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/04/28 20:45:52 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

ERROR=srcs/error/ft_errno.c\

LINE_EDITING=srcs/line_editing/check_symb.c\
			srcs/line_editing/line_editing.c\
			srcs/line_editing/line_editing2.c\

AUTOCOM=srcs/autocom/autocom.c\

MAKE=srcs/make/buff_editing.c\
	srcs/make/env.c\
	srcs/make/env2.c\
	srcs/make/process.c\
	srcs/make/term_make.c\

PARSER=srcs/parser/parse.c\

READING=srcs/reading/reading.c\

SIGNAL=srcs/signal/signal.c\

TERM=srcs/term/term.c\

BUILTINS=srcs/builtins/cd/cd.c\
		srcs/builtins/echo/echo.c\
		srcs/builtins/env/env.c\
		srcs/builtins/setenv/setenv.c\
		srcs/builtins/unsetenv/unsetenv.c\

SRCS=$(ERROR) $(LINE_EDITING) $(AUTOCOM) $(MAKE) $(PARSER) $(READING) $(SIGNAL) $(TERM) $(BUILTINS)

INCLUDES=includes

INCLUDES_LIB=libft/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all:$(NAME)

$(NAME):
			make re -C $(LIB)
			gcc $(EXTRA_FLAGS) -o $(NAME) $(SRCS) -I $(INCLUDES) -I $(INCLUDES_LIB) -L $(LIB) -lft

clean:
			make clean -C $(LIB)

fclean: clean
			make fclean -C $(LIB)
			rm -f $(NAME)

re: fclean all