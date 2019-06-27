# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/06/27 21:00:35 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

ERROR=srcs/error/ft_errno.c\

LINE_EDITING=srcs/line_editing/check_symb.c\
			srcs/line_editing/quotes.c\
			srcs/line_editing/cut_copy_paste.c\
			srcs/line_editing/highlight.c\
			srcs/line_editing/print_printable.c\
			srcs/line_editing/print_move.c\
			srcs/line_editing/print_move2.c\
			srcs/line_editing/history.c\
			srcs/line_editing/get_and_check.c\
			srcs/line_editing/init.c\
			srcs/line_editing/free.c\

AUTOCOM=srcs/autocom/autocom.c\

MAKE=srcs/make/buff_editing.c\
	srcs/make/buff_editing2.c\
	srcs/make/env.c\
	srcs/make/env2.c\
	srcs/make/process.c\

HASH_TABLE=srcs/hash_table/hash_table.c\
		srcs/hash_table/hash_table2.c\
		srcs/hash_table/hash_table3.c\

HISTORY=srcs/history/make_history.c\
		srcs/history/make_history2.c\

PARSER=srcs/parser/parse.c\

READING=srcs/reading/reading.c\

SIGNAL=srcs/signal/signal.c\

TERM=srcs/term/term.c\

BUILTINS=srcs/builtins/cd/cd.c\
		srcs/builtins/echo/echo.c\
		srcs/builtins/env/env.c\
		srcs/builtins/setenv/setenv.c\
		srcs/builtins/unsetenv/unsetenv.c\
		srcs/builtins/hash/hash.c\
		srcs/builtins/history/history.c\

EXEC=srcs/exec/exec.c

SRC_SEARCH = $(TERM) $(MAKE) $(ERROR) $(HISTORY) $(HASH_TABLE) $(SIGNAL) $(READING) $(LINE_EDITING) $(PARSER) $(EXEC) $(BUILTINS)

SRC = $(wildcard $(SRC_SEARCH))

OBJ = $(SRC:.c=.o)

INCLUDES=includes

INCLUDES_LIB=libft/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all:$(NAME)

$(NAME): $(OBJ) libft
	gcc -g $(OBJ) -o $@ -L $(LIB) -lft -lncurses

%.o: %.c
	gcc -c $< -o $@ $(EXTRA_FLAGS) -I $(INCLUDES) -I $(INCLUDES_LIB)

.PHONY: libft

libft:
	make -C libft

clean:
	make clean -C $(LIB)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -rf $(NAME)

re: fclean all
