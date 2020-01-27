# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2020/01/27 20:53:11 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 42sh

load_script := load_git_repo.sh

dir_error := error

dir_ft_readline := ft_readline

dir_bin_table := hash_table

dir_interpretator := interpretator

dir_term := term

dir_environ := environ

dir_builtins := builtins

dir_jobs := jobs

dir_lex := lex

lib_dir := libraries

objs = $(wildcard $(dir_bin_table)/objs/*.o)\
		$(wildcard $(dir_jobs)/objs/*.o)\
		$(wildcard $(dir_builtins)/objs/*.o)\
		$(wildcard $(dir_environ)/objs/*.o)\
		$(wildcard $(dir_error)/objs/*.o)\
		$(wildcard $(dir_interpretator)/objs/*.o)\
		$(wildcard $(dir_ft_readline)/objs/*.o)\
		$(wildcard $(dir_term)/objs/*.o)\
		$(wildcard $(dir_lex)/objs/*.o)\

.LIBPATTERNS := "lib%.a"

cc := gcc

repo := https://github.com/OlegMulko/LibProjects42.git

lib_flags := -L libraries/libft -L libraries/libstr -L libraries/libdir -L libraries/libdar\
			-L libraries/libhash -lft -lstr -ldir -ldar -lhash -lncurses

.PHONY: compilation link $(dir_bin_table)\
$(dir_builtins) $(dir_environ) $(dir_jobs) $(dir_error) $(dir_interpretator)\
$(dir_ft_readline) $(dir_term) $(dir_lex)\
lall lclean lfclean clean fclean re

all: $(name)

$(name): $(lib_dir) $(dir_bin_table) $(dir_builtins) $(dir_environ) $(dir_jobs) $(dir_error) $(dir_interpretator)\
$(dir_ft_readline) $(dir_term) $(dir_lex)
	$(cc) $(objs) -o $(name) $(lib_flags)

$(dir_bin_table):
	$(MAKE) --no-print-directory -C $(dir_bin_table)

$(dir_jobs):
	$(MAKE) --no-print-directory -C $(dir_jobs)

$(dir_builtins):
	$(MAKE) --no-print-directory -C $(dir_builtins)

$(dir_environ):
	$(MAKE) --no-print-directory -C $(dir_environ)

$(dir_error):
	$(MAKE) --no-print-directory -C $(dir_error)

$(dir_interpretator):
	$(MAKE) --no-print-directory -C $(dir_interpretator)

$(dir_ft_readline):
	$(MAKE) --no-print-directory -C $(dir_ft_readline)

$(dir_term):
	$(MAKE) --no-print-directory -C $(dir_term)

$(dir_lex):
	$(MAKE) --no-print-directory -C $(dir_lex)

$(lib_dir):
	./$(load_script) $(repo) $(lib_dir)

lclean: $(lib_dir)
	$(MAKE) clean --no-print-directory -C $(lib_dir)

lfclean: $(lib_dir)
	$(MAKE) fclean --no-print-directory -C $(lib_dir)

clean: lclean
	$(MAKE) clean --no-print-directory -C $(dir_bin_table)
	$(MAKE) clean --no-print-directory -C $(dir_builtins)
	$(MAKE) clean --no-print-directory -C $(dir_environ)
	$(MAKE) clean --no-print-directory -C $(dir_jobs)
	$(MAKE) clean --no-print-directory -C $(dir_error)
	$(MAKE) clean --no-print-directory -C $(dir_interpretator)
	$(MAKE) clean --no-print-directory -C $(dir_ft_readline)
	$(MAKE) clean --no-print-directory -C $(dir_term)
	$(MAKE) clean --no-print-directory -C $(dir_lex)

fclean: $(lib_dir) lfclean
	$(MAKE) clean --no-print-directory -C $(dir_bin_table)
	$(MAKE) clean --no-print-directory -C $(dir_builtins)
	$(MAKE) clean --no-print-directory -C $(dir_environ)
	$(MAKE) clean --no-print-directory -C $(dir_jobs)
	$(MAKE) clean --no-print-directory -C $(dir_error)
	$(MAKE) clean --no-print-directory -C $(dir_interpretator)
	$(MAKE) clean --no-print-directory -C $(dir_ft_readline)
	$(MAKE) clean --no-print-directory -C $(dir_term)
	$(MAKE) clean --no-print-directory -C $(dir_lex)
	rm -rf $(name)

re: $(lib_dir)
	$(MAKE) --no-print-directory fclean
	$(MAKE) --no-print-directory all
