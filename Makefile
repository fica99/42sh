# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/07/05 18:29:05 by aashara-         ###   ########.fr        #
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

AUTOCOM=srcs/autocom/ac_autocom.c\
		srcs/autocom/ac_dir.c\
		srcs/autocom/ac_parse.c\
		srcs/autocom/ac_options.c\
		srcs/autocom/ac_move_cursor.c\
		srcs/autocom/ac_print_params.c\
		srcs/autocom/ac_print.c\
		srcs/autocom/ac_recalc_index.c\

MAKE=srcs/make/buff_editing.c\
	srcs/make/env.c\
	srcs/make/env2.c\
	srcs/make/process.c\

HASH_TABLE=srcs/hash_table/hash_table.c\
		srcs/hash_table/hash_table2.c\
		srcs/hash_table/free_hash_table.c\

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

SRC_SEARCH = $(TERM) $(MAKE) $(ERROR) $(HISTORY) $(HASH_TABLE) $(SIGNAL) $(READING) $(LINE_EDITING) $(PARSER) $(EXEC) $(BUILTINS) $(AUTOCOM)

SRC = $(wildcard $(SRC_SEARCH))

OBJ = $(SRC:.c=.o)

INCLUDES=includes

INCLUDES_LIB=LibProjects42/libft/includes

INCLUDES_FTSTR=LibProjects42/ftstr/includes

INCLUDES_FTDIR=LibProjects42/ftdir/includes

INCLUDES_FTDAR=LibProjects42/ftdar/includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB1=LibProjects42/libft

LIB2=LibProjects42/ftstr

LIB3=LibProjects42/ftdir

LIB4=LibProjects42/ftdar

REPO=https://github.com/OlegMulko/LibProjects42.git

all:$(NAME)

$(NAME): loadlib $(OBJ)
	gcc $(OBJ) -o $@ -L $(LIB1) -L $(LIB2) -L $(LIB3) -L $(LIB4) -lft -lftstr -lftdir -lftdar -lncurses

%.o: %.c
	gcc -c $< -o $@ $(EXTRA_FLAGS) -I $(INCLUDES) -I $(INCLUDES_LIB) -I $(INCLUDES_FTSTR) -I $(INCLUDES_FTDIR) -I $(INCLUDES_FTDAR)

loadlib:
	./LoadLibProjects42.sh $(REPO) LibProjects42

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
