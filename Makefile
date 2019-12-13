# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 42sh

lib_dir := libraries

inc_dir := includes

load_script := load_git_repo.sh

lib_archive := $(addprefix $(lib_dir)/, lib_archive)

dir_error := error

dir_ft_readline := ft_readline

dir_bin_table := bin_table

dir_interpretator := interpretator

dir_term := term

dir_environ := environ

dir_builtins := builtins

dir_jobs := jobs

dir_sub := sub

dir_calc := calc

dir_lex := lex

dir_signal := signal

objs := $(wildcard $(addprefix $(dir_bin_table), /**/*.o))\
		$(wildcard $(addprefix $(dir_jobs), /**/*.o))\
		$(wildcard $(addprefix $(dir_builtins), /**/*.o))\
		$(wildcard $(addprefix $(dir_environ), /**/*.o))\
		$(wildcard $(addprefix $(dir_error), /**/*.o))\
		$(wildcard $(addprefix $(dir_interpretator), /**/*.o))\
		$(wildcard $(addprefix $(dir_sub), /**/*.o))\
		$(wildcard $(addprefix $(dir_ft_readline), /**/*.o))\
		$(wildcard $(addprefix $(dir_prompt), /**/*.o))\
		$(wildcard $(addprefix $(dir_term), /**/*.o))\
		$(wildcard $(addprefix $(dir_calc), /**/*.o))\
		$(wildcard $(addprefix $(dir_lex), /**/*.o))\
		$(wildcard $(addprefix $(dir_signal), /**/*.o))\

.LIBPATTERNS := "lib%.a"

cc := gcc

repo := https://github.com/OlegMulko/LibProjects42.git

lib_flags := -lft -lstr -ldir -ldar -lfifo -lstack -lncurses -lhash

.PHONY: loadlibs removelibs compilation link $(dir_bin_table)\
$(dir_builtins) $(dir_environ) $(dir_jobs) $(dir_error) $(dir_interpretator)\
$(dir_ft_readline) $(dir_term) $(dir_calc) $(dir_lex) $(dir_signal)\
lall llall llclean llfclean lfclean oclean clean fclean re

all: $(name)

$(name): $(lib_dir) lall
	@$(MAKE) --no-print-directory compilation
	@$(MAKE) --no-print-directory link

link:
	@$(cc) -g -O0 $(objs) -o $(name) -L $(lib_archive) $(lib_flags)
	@echo "\033[36mCreate binary file $(CURDIR)/$(name)\033[0m"

compilation:
	@$(MAKE) --no-print-directory $(dir_bin_table)
	@$(MAKE) --no-print-directory $(dir_builtins)
	@$(MAKE) --no-print-directory $(dir_environ)
	@$(MAKE) --no-print-directory $(dir_jobs)
	@$(MAKE) --no-print-directory $(dir_error)
	@$(MAKE) --no-print-directory $(dir_interpretator)
	@$(MAKE) --no-print-directory $(dir_ft_readline)
	@$(MAKE) --no-print-directory $(dir_term)
	@$(MAKE) --no-print-directory $(dir_calc)
	@$(MAKE) --no-print-directory $(dir_lex)
	@$(MAKE) --no-print-directory $(dir_signal)

$(objs):
	@$(MAKE) --no-print-directory compilation

$(dir_bin_table):
	@$(MAKE) --no-print-directory -C $(dir_bin_table)

$(dir_jobs):
	@$(MAKE) --no-print-directory -C $(dir_jobs)

$(dir_builtins):
	@$(MAKE) --no-print-directory -C $(dir_builtins)

$(dir_environ):
	@$(MAKE) --no-print-directory -C $(dir_environ)

$(dir_error):
	@$(MAKE) --no-print-directory -C $(dir_error)

$(dir_interpretator):
	@$(MAKE) --no-print-directory -C $(dir_interpretator)

$(dir_ft_readline):
	@$(MAKE) --no-print-directory -C $(dir_ft_readline)

$(dir_term):
	@$(MAKE) --no-print-directory -C $(dir_term)

$(dir_calc):
	@$(MAKE) --no-print-directory -C $(dir_calc)

$(dir_lex):
	@$(MAKE) --no-print-directory -C $(dir_lex)

$(dir_signal):
	@$(MAKE) --no-print-directory -C $(dir_signal)

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
	@$(MAKE) clean --no-print-directory -C $(dir_jobs)
	@$(MAKE) clean --no-print-directory -C $(dir_error)
	@$(MAKE) clean --no-print-directory -C $(dir_interpretator)
	@$(MAKE) clean --no-print-directory -C $(dir_ft_readline)
	@$(MAKE) clean --no-print-directory -C $(dir_term)
	@$(MAKE) clean --no-print-directory -C $(dir_calc)
	@$(MAKE) clean --no-print-directory -C $(dir_lex)
	@$(MAKE) clean --no-print-directory -C $(dir_signal)


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
