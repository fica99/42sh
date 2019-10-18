# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/10/18 20:29:06 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 21sh

lib_dir := libraries

srcs_dir := srcs

obj_dir := obj

inc_dir := includes

load_script := load_git_repo.sh

lib_archive := $(addprefix $(lib_dir)/, lib_archive)

srcs_error := error.c\

dir_error := error

srcs_line_editing := check.c\
		cord.c\
		free_line.c\
		init_line.c\
		k_cur_movements.c\
		k_cur_movements2.c\
		k_history.c\
		k_highlight.c\
		k_print.c\
		print.c\
		symb.c\
		templates.c\
		cur_movements.c\

dir_line_editing := line_editing

srcs_bin_table := bin_table.c\

dir_bin_table := bin_table

srcs_history := history.c\

dir_history := history

srcs_parser := ast.c\
		init_free_parser.c\
		ast_other.c\

dir_parser := parser

srcs_interpretator := interpretator.c\
		rredir.c\
		lredir.c\
		pipes.c\
		dup_fd.c\
		exec.c\
		spec_symb.c\
		parse_quotes.c\
		aggr_fd.c\
		process.c\

dir_interpretator := interpretator

srcs_reading := reading.c\
		read_mode.c\

dir_reading := reading

srcs_term := ft_term.c\
		global_var.c\

dir_term := term

srcs_lexer = load_lexer.c\
		load_matrix.c\
		clear_lexer.c\
		lexer.c\
		check_tokens.c\
		init_tokens.c\
		union_token.c\
		different_tokens.c\
		check_matrixs.c\
		get_token.c\
		get_token2.c\
		error_token.c\

dir_lexer := lexer

srcs_environ = get_env.c\
		init_environ.c\

dir_environ := environ

srcs_signal = signal.c\

dir_signal := signal

srcs_prompt := prompt.c\
		prompt_other.c\
		path.c\

dir_prompt := prompt

srcs_builtins := cd.c\
		echo.c\
		env.c\
		setenv.c\
		unsetenv.c\
		hash.c\
		ft_history.c\

dir_builtins := builtins

.LIBPATTERNS := "lib%.a"

obj_error:= $(addprefix srcs/$(dir_error)/obj/, $(srcs_error:.c=.o))

obj_environ:= $(addprefix srcs/$(dir_environ)/obj/, $(srcs_environ:.c=.o))

obj_bin_table := $(addprefix srcs/$(dir_bin_table)/obj/, $(srcs_bin_table:.c=.o))

obj_builtins := $(addprefix srcs/$(dir_builtins)/obj/, $(srcs_builtins:.c=.o))

obj_history := $(addprefix srcs/$(dir_history)/obj/, $(srcs_history:.c=.o))

obj_interpretator := $(addprefix srcs/$(dir_interpretator)/obj/, $(srcs_interpretator:.c=.o))

obj_lexer := $(addprefix srcs/$(dir_lexer)/obj/, $(srcs_lexer:.c=.o))

obj_line_editing := $(addprefix srcs/$(dir_line_editing)/obj/, $(srcs_line_editing:.c=.o))

obj_parser := $(addprefix srcs/$(dir_parser)/obj/, $(srcs_parser:.c=.o))

obj_prompt := $(addprefix srcs/$(dir_prompt)/obj/, $(srcs_prompt:.c=.o))

obj_reading := $(addprefix srcs/$(dir_reading)/obj/, $(srcs_reading:.c=.o))

obj_signal := $(addprefix srcs/$(dir_signal)/obj/, $(srcs_signal:.c=.o))

obj_term := $(addprefix srcs/$(dir_term)/obj/, $(srcs_term:.c=.o))

objects := $(obj_bin_table) $(obj_builtins) $(obj_environ) $(obj_error) $(obj_lexer) $(obj_interpretator) $(obj_line_editing)\
	$(obj_term) $(obj_signal) $(obj_reading) $(obj_prompt) $(obj_parser) $(obj_history)

cc := gcc

repo := https://github.com/OlegMulko/LibProjects42.git

lib_flags := -lft -lstr -ldir -ldar -lfifo -lstack -lncurses -lhash

.PHONY: all loadlibs objs removelibs lall llall llclean llfclean lfclean oclean clean fclean re

all: $(name)

$(name): $(lib_dir) lall
	@$(MAKE) --no-print-directory objs
	@echo "\033[32m\033[1m--->Create binary file $(CURDIR)/$(name)\033[0m"
	@$(cc) $(objects) -o $@ -L $(lib_archive) $(lib_flags)

objs:
	@$(MAKE) --no-print-directory -C srcs/$(dir_bin_table)
	@$(MAKE) --no-print-directory -C srcs/$(dir_builtins)
	@$(MAKE) --no-print-directory -C srcs/$(dir_environ)
	@$(MAKE) --no-print-directory -C srcs/$(dir_error)
	@$(MAKE) --no-print-directory -C srcs/$(dir_history)
	@$(MAKE) --no-print-directory -C srcs/$(dir_interpretator)
	@$(MAKE) --no-print-directory -C srcs/$(dir_lexer)
	@$(MAKE) --no-print-directory -C srcs/$(dir_line_editing)
	@$(MAKE) --no-print-directory -C srcs/$(dir_parser)
	@$(MAKE) --no-print-directory -C srcs/$(dir_prompt)
	@$(MAKE) --no-print-directory -C srcs/$(dir_reading)
	@$(MAKE) --no-print-directory -C srcs/$(dir_signal)
	@$(MAKE) --no-print-directory -C srcs/$(dir_term)

loadlibs:
	@echo "\033[0;35m\033[1m--->Load Libraries\033[0m"
	@./$(load_script) $(repo) $(lib_dir)
	@echo "\033[0;35m\033[1m--->Finish loading\033[0m"

$(lib_dir):
	@echo "\033[0;35m\033[1m--->Load Libraries\033[0m"
	@./$(load_script) $(repo) $(lib_dir)
	@echo "\033[0;35m\033[1m--->Finish loading\033[0m"

removelibs:
	@echo "\033[0;35m\033[1m--->Remove Libraries\033[0m"
	@rm -rf $(lib_dir)

lall: $(lib_dir)
	@echo "\033[0;30m\033[1m--->Start compiling libraries archive\033[0m"
	@$(MAKE) all --no-print-directory -C $(lib_dir)
	@echo "\033[0;30m\033[1m--->Finish libraries archieve compilation\033[0m"
	@echo "\033[0;30m\033[1m--->Finish getting libraries archieve\033[0m"

llall: $(lib_dir)
	@$(MAKE) lall --no-print-directory -C $(lib_dir)

llclean: $(lib_dir)
	@$(MAKE) lclean --no-print-directory -C $(lib_dir)

llfclean: $(lib_dir)
	@$(MAKE) lfclean --no-print-directory -C $(lib_dir)

lfclean: $(lib_dir)
	@$(MAKE) fclean --no-print-directory -C $(lib_dir)

oclean:
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_bin_table)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_builtins)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_environ)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_error)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_history)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_interpretator)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_lexer)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_line_editing)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_parser)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_prompt)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_reading)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_signal)
	@$(MAKE) clean --no-print-directory -C srcs/$(dir_term)

clean: $(lib_dir)
	@$(MAKE) --no-print-directory oclean
	@$(MAKE) --no-print-directory lfclean

fclean: $(lib_dir)
	@$(MAKE) --no-print-directory clean
	@echo "\033[36m\033[1m--->Remove $(CURDIR)/$(name)\033[0m"
	@-rm -rf $(name)

re: $(lib_dir)
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
