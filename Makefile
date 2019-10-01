# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/10/01 14:56:48 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 21sh

lib_dir := libraries

srcs_dir := srcs

obj_dir := obj

inc_dir := includes

load_script := load_git_repo.sh

lib_archive := $(addprefix $(lib_dir)/, lib_archive)

srcs_error := error/error.c\

srcs_line_editing := line_editing/check.c\
		line_editing/cord.c\
		line_editing/data.c\
		line_editing/free_line.c\
		line_editing/init_line.c\
		line_editing/k_cur_movements.c\
		line_editing/k_cur_movements2.c\
		line_editing/k_history.c\
		line_editing/k_highlight.c\
		line_editing/k_print.c\
		line_editing/print.c\
		line_editing/symb.c\
		line_editing/templates.c\
		line_editing/cur_movements.c\

srcs_bin_table := bin_table/bin_table.c\
		bin_table/free_bin_table.c\

srcs_history := history/history.c\

srcs_parser := parser/ast.c\
		parser/init_free_parser.c\
		parser/ast_other.c\

srcs_interpretator := interpretator/interpretator.c\
		interpretator/rredir.c\
		interpretator/lredir.c\
		interpretator/pipes.c\
		interpretator/dup_fd.c\
		interpretator/exec.c\
		interpretator/spec_symb.c\
		interpretator/parse_quotes.c\
		interpretator/aggr_fd.c\
		interpretator/process.c\

srcs_reading := reading/reading.c\
		reading/read_mode.c\

srcs_term := term/ft_term.c\
		term/global_var.c\

srcs_prompt := prompt/prompt.c\
		prompt/prompt_other.c\
		prompt/path.c\

srcs_builtins := builtins/cd/cd.c\
		builtins/echo/echo.c\
		builtins/env/env.c\
		builtins/setenv/setenv.c\
		builtins/unsetenv/unsetenv.c\
		builtins/hash/hash.c\
		builtins/history/ft_history.c\

srcs_lexer = lexer/load_lexer.c\
		lexer/load_matrix.c\
		lexer/clear_lexer.c\
		lexer/lexer.c\
		lexer/check_tokens.c\
		lexer/init_tokens.c\
		lexer/union_token.c\
		lexer/different_tokens.c\
		lexer/check_matrixs.c\
		lexer/get_token.c\
		lexer/get_token2.c\
		lexer/error_token.c\

srcs_environ = environ/get_env.c\
		environ/init_environ.c\

srcs_signal = signal/signal.c\

builtins_dir := builtins

srcs_files := $(srcs_term)\
			$(srcs_prompt)\
			$(srcs_error)\
			$(srcs_history)\
			$(srcs_bin_table)\
			$(srcs_reading)\
			$(srcs_line_editing)\
			$(srcs_builtins)\
			$(srcs_lexer)\
			$(srcs_parser)\
			$(srcs_interpretator)\
			$(srcs_environ)\
			$(srcs_signal)\

.LIBPATTERNS := "lib%.a"

obj_files := $(srcs_files:.c=.o)

objects := $(addprefix $(obj_dir)/, $(obj_files))

dirs := $(dir $(srcs_files))

obj_dirs := $(addprefix $(obj_dir)/, $(dirs))

cc := gcc

cflags := -Wall -Wextra -Werror

repo := https://github.com/OlegMulko/LibProjects42.git

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdir := $(addprefix $(addprefix $(lib_dir)/, libdir/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_libstack := $(addprefix $(addprefix $(lib_dir)/, libstack/), includes)

includes_libfifo := $(addprefix $(addprefix $(lib_dir)/, libfifo/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

lib_flags := -lft -lstr -ldir -ldar -lfifo -lstack -lncurses -lhash

includes := -I $(inc_dir) -I $(includes_libdar) -I $(includes_libdir) \
	-I $(includes_libfifo) -I $(includes_libft) -I $(includes_libstack) -I $(includes_libstr) -I $(includes_libhash)

.PHONY: all loadlibs removelibs lall llall llclean llfclean lfclean oclean clean fclean re

all: $(name)

$(name): $(lib_dir) lall $(obj_dir) $(objects)
	@echo "\033[32m\033[1m--->Create binary file $(CURDIR)/$(name)\033[0m"
	@$(cc) $(objects) -o $@ -L $(lib_archive) $(lib_flags)

$(obj_dir):
	@echo "\033[32m\033[1m--->Create object directory $(CURDIR)/$(obj_dir)\033[0m"
	@mkdir -p $(obj_dir) $(obj_dir)/$(builtins_dir) $(obj_dirs)
	@echo "\033[32m\033[1m--->Compile sources:\033[0m"
	@$(MAKE) --no-print-directory $(objects)

$(obj_dir)/%.o:$(srcs_dir)/%.c
	@echo "\033[31m\033[1m--->Create object file $(CURDIR)/$@\033[0m"
	@$(cc) $(cflags) $(includes) -o $@ -c $<

$(lib_dir):
		@$(MAKE) --no-print-directory loadlibs

loadlibs:
	@echo "\033[0;35m\033[1m--->Load Libraries\033[0m"
	@./$(load_script) $(repo) $(lib_dir)
	@echo "\033[0;35m\033[1m--->Finish loading\033[0m"

removelibs:
	@echo "\033[0;35m\033[1m--->Remove Libraries\033[0m"
	@rm -rf $(lib_dir)

lall:
	@echo "\033[0;30m\033[1m--->Start compiling libraries archive\033[0m"
	@$(MAKE) all --no-print-directory -C $(lib_dir)
	@echo "\033[0;30m\033[1m--->Finish libraries archieve compilation\033[0m"
	@echo "\033[0;30m\033[1m--->Finish getting libraries archieve\033[0m"

llall:
	@$(MAKE) lall --no-print-directory -C $(lib_dir)

llclean:
	@$(MAKE) lclean --no-print-directory -C $(lib_dir)

llfclean:
	@$(MAKE) lfclean --no-print-directory -C $(lib_dir)

lfclean:
	@$(MAKE) fclean --no-print-directory -C $(lib_dir)

oclean:
	@echo "\033[36m\033[1m--->Remove $(CURDIR)/$(obj_dir)\033[0m"
	@-rm -rf $(obj_dir)

clean:
	@$(MAKE) --no-print-directory oclean
	@$(MAKE) --no-print-directory lfclean

fclean:
	@$(MAKE) --no-print-directory clean
	@echo "\033[36m\033[1m--->Remove $(CURDIR)/$(name)\033[0m"
	@-rm -rf $(name)

re:
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
