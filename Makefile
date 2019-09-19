# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/09/19 21:52:12 by aashara-         ###   ########.fr        #
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

srcs_line_editing := line_editing/check_symb.c\
			line_editing/cut_copy_paste.c\
			line_editing/highlight.c\
			line_editing/print_printable.c\
			line_editing/print_move.c\
			line_editing/print_move_other.c\
			line_editing/history.c\
			line_editing/get_and_check.c\
			line_editing/init.c\
			line_editing/free.c\
			line_editing/quotes.c\
			line_editing/heredoc.c\

srcs_autocom := autocom/ac_autocom.c\
		autocom/ac_parse.c\
		autocom/ac_options.c\
		autocom/ac_options2.c\
		autocom/ac_move_cursor.c\
		autocom/ac_print_params.c\
		autocom/ac_print.c\
		autocom/ac_recalc_index.c\

srcs_make := make/buff_editing.c\
		make/env.c\
		make/env2.c\
		make/process.c\

srcs_bin_table := bin_table/bin_table.c\
		bin_table/free_bin_table.c\

srcs_history := history/make_history.c\
		history/make_history_other.c\

srcs_parser := parser/ast.c\
		parser/init_free_parser.c\
		parser/ast_other.c\

srcs_interpretator := interpretator/interpretator.c\
		interpretator/rredir.c\
		interpretator/lredir.c\
		interpretator/pipes.c\
		interpretator/dup_fd.c\
		interpretator/aggr_fd.c\
		interpretator/exec.c\
		interpretator/spec_symb.c\
		interpretator/parse_quotes.c\

srcs_reading := reading/reading.c\
		reading/canon_mode.c\

srcs_signal := signal/signal.c\

srcs_term := term/ft_term.c\

srcs_prompt := prompt/prompt.c\
		prompt/prompt_other.c\

srcs_builtins := builtins/cd/cd.c\
		builtins/echo/echo.c\
		builtins/env/ft_env.c\
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
		lexer/debug_lexer.c\


builtins_dir := builtins

srcs_files := $(srcs_term)\
			$(srcs_prompt)\
			$(srcs_make)\
			$(srcs_error)\
			$(srcs_history)\
			$(srcs_bin_table)\
			$(srcs_signal)\
			$(srcs_reading)\
			$(srcs_line_editing)\
			$(srcs_builtins)\
			$(srcs_autocom)\
			$(srcs_lexer)\
			$(srcs_parser)\
			$(srcs_interpretator)\

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

header := includes/ft_term.h includes/autocom/autocom.h includes/builtins/cd/cd.h includes/builtins/echo/echo.h \
	includes/builtins/env/env.h includes/builtins/hash/hash.h includes/builtins/his/his.h \
	includes/builtins/setenv/setenv.h includes/builtins/unsetenv/unsetenv.h includes/error/error.h \
	includes/bin_table/bin_table.h includes/history/history.h includes/interpretator/interpretator.h \
	includes/lexer/lexer.h includes/line_editing/line_editing.h includes/macro/colour.h \
	includes/make/make.h includes/parser/parser.h includes/prompt/prompt.h \
	includes/reading/reading.h includes/signal/signal.h includes/term/term.headers

includes := -I $(inc_dir) -I $(includes_libdar) -I $(includes_libdir) \
	-I $(includes_libfifo) -I $(includes_libft) -I $(includes_libstack) -I $(includes_libstr) -I $(includes_libhash)

.PHONY: all loadlibs removelibs lall llall llclean llfclean lfclean oclean clean fclean re

all: $(name)

$(name): $(lib_dir) lall $(obj_dir) $(objects)
	@echo "\033[32m\033[1m--->Create binary file $(CURDIR)/$(name)\033[0m"
	@$(cc) -g -O0 $(objects) -o $@ -L $(lib_archive) $(lib_flags)

$(obj_dir):
	@echo "\033[32m\033[1m--->Create object directory $(CURDIR)/$(obj_dir)\033[0m"
	@mkdir -p $(obj_dir) $(obj_dir)/$(builtins_dir) $(obj_dirs)
	@echo "\033[32m\033[1m--->Compile sources:\033[0m"
	@$(MAKE) --no-print-directory $(objects)

$(obj_dir)/%.o:$(srcs_dir)/%.c
	@echo "\033[31m\033[1m--->Create object file $(CURDIR)/$@\033[0m"
	@$(cc) -g -O0 $(cflags) $(includes) -o $@ -c $<

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
