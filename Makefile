# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/10/21 15:19:48 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 42sh

lib_dir := libraries

inc_dir := includes

load_script := load_git_repo.sh

lib_archive := $(addprefix $(lib_dir)/, lib_archive)

dir_error := error

dir_read_line := read_line

dir_bin_table := bin_table

dir_history := history

dir_parser := parser

dir_interpretator := interpretator

dir_term := term

dir_lexer := lexer

dir_environ := environ

dir_signal := signal

dir_prompt := prompt

dir_builtins := builtins

srcs := $(wildcard $(addprefix $(dir_bin_table), /**/*.c))\
		$(wildcard $(addprefix $(dir_builtins), /**/*.c))\
		$(wildcard $(addprefix $(dir_environ), /**/*.c))\
		$(wildcard $(addprefix $(dir_error), /**/*.c))\
		$(wildcard $(addprefix $(dir_history), /**/*.c))\
		$(wildcard $(addprefix $(dir_interpretator), /**/*.c))\
		$(wildcard $(addprefix $(dir_lexer), /**/*.c))\
		$(wildcard $(addprefix $(dir_read_line), /**/*.c))\
		$(wildcard $(addprefix $(dir_parser), /**/*.c))\
		$(wildcard $(addprefix $(dir_prompt), /**/*.c))\
		$(wildcard $(addprefix $(dir_signal), /**/*.c))\
		$(wildcard $(addprefix $(dir_term), /**/*.c))\

objs := $(subst srcs,objs,$(srcs:.c=.o))

.LIBPATTERNS := "lib%.a"

cc := gcc

repo := https://github.com/OlegMulko/LibProjects42.git

lib_flags := -lft -lstr -ldir -ldar -lfifo -lstack -lncurses -lhash

.PHONY: all loadlibs removelibs compilation lall llall llclean llfclean lfclean oclean clean fclean re

all: $(name)

$(name): $(lib_dir) lall
	@$(MAKE) --no-print-directory compilation
	@$(cc) $(objs) -o $@ -L $(lib_archive) $(lib_flags)
	@echo "\033[35m--->Create binary file $(CURDIR)/$(name)\033[0m"

compilation:
	@$(MAKE) --no-print-directory -C $(dir_bin_table)
	@$(MAKE) --no-print-directory -C $(dir_builtins)
	@$(MAKE) --no-print-directory -C $(dir_environ)
	@$(MAKE) --no-print-directory -C $(dir_error)
	@$(MAKE) --no-print-directory -C $(dir_history)
	@$(MAKE) --no-print-directory -C $(dir_interpretator)
	@$(MAKE) --no-print-directory -C $(dir_lexer)
	@$(MAKE) --no-print-directory -C $(dir_read_line)
	@$(MAKE) --no-print-directory -C $(dir_parser)
	@$(MAKE) --no-print-directory -C $(dir_prompt)
	@$(MAKE) --no-print-directory -C $(dir_signal)
	@$(MAKE) --no-print-directory -C $(dir_term)

loadlibs:
	@echo "\033[32mLoad Libraries\033[0m"
	@./$(load_script) $(repo) $(lib_dir)

$(lib_dir):
	@echo "\033[32mLoad Libraries\033[0m"
	@./$(load_script) $(repo) $(lib_dir)

removelibs:
	@echo "\033[31mRemove Libraries\033[0m"
	@rm -rf $(lib_dir)

lall: $(lib_dir)
	@$(MAKE) all --no-print-directory -C $(lib_dir)

llall: $(lib_dir)
	@$(MAKE) lall --no-print-directory -C $(lib_dir)

llclean: $(lib_dir)
	@$(MAKE) lclean --no-print-directory -C $(lib_dir)

llfclean: $(lib_dir)
	@$(MAKE) lfclean --no-print-directory -C $(lib_dir)

lfclean: $(lib_dir)
	@$(MAKE) fclean --no-print-directory -C $(lib_dir)

oclean:
	@$(MAKE) clean --no-print-directory -C $(dir_bin_table)
	@$(MAKE) clean --no-print-directory -C $(dir_builtins)
	@$(MAKE) clean --no-print-directory -C $(dir_environ)
	@$(MAKE) clean --no-print-directory -C $(dir_error)
	@$(MAKE) clean --no-print-directory -C $(dir_history)
	@$(MAKE) clean --no-print-directory -C $(dir_interpretator)
	@$(MAKE) clean --no-print-directory -C $(dir_lexer)
	@$(MAKE) clean --no-print-directory -C $(dir_read_line)
	@$(MAKE) clean --no-print-directory -C $(dir_parser)
	@$(MAKE) clean --no-print-directory -C $(dir_prompt)
	@$(MAKE) clean --no-print-directory -C $(dir_signal)
	@$(MAKE) clean --no-print-directory -C $(dir_term)

clean: $(lib_dir)
	@$(MAKE) --no-print-directory oclean
	@$(MAKE) --no-print-directory lfclean

fclean: $(lib_dir)
	@$(MAKE) --no-print-directory clean
	@echo "\033[31mRemove $(CURDIR)/$(name)\033[0m"
	@-rm -rf $(name)

re: $(lib_dir)
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all
