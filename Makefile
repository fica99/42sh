# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2020/02/04 19:22:27 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 42sh

lib_dir := libraries

main_dir := main

ft_readline_dir := ft_readline

lex_dir := lex

cc := gcc

lib_flags := -L libraries/libft -L libraries/libdir -L libraries/libdar\
			-L libraries/libhash -L libraries/libstr -lft -ldir -ldar -lstr -lhash -lncurses

srcs_dir := srcs

srcs := $(wildcard $(main_dir)/$(srcs_dir)/*.c)\
		$(wildcard $(ft_readline_dir)/$(srcs_dir)/*.c)\
		$(wildcard $(lex_dir)/$(srcs_dir)/*.c)

objs_dir := objs

objs := $(patsubst $(main_dir)/$(srcs_dir)/%.c,$(main_dir)/$(objs_dir)/%.o, $(srcs))

objs := $(patsubst $(ft_readline_dir)/$(srcs_dir)/%.c,$(ft_readline_dir)/$(objs_dir)/%.o, $(objs))

objs := $(patsubst $(lex_dir)/$(srcs_dir)/%.c,$(lex_dir)/$(objs_dir)/%.o, $(objs))

.PHONY: all lall lclean lfclean clean fclean re $(main_dir) $(ft_readline_dir) $(lex_dir)

all: lall $(ft_readline_dir) $(lex_dir) $(main_dir) $(name)

$(name): $(objs)
	$(cc) $(objs) -o $(name) $(lib_flags)

$(main_dir):
	$(MAKE) all --no-print-directory -C $(main_dir)

$(ft_readline_dir):
	$(MAKE) all --no-print-directory -C $(ft_readline_dir)

$(lex_dir):
	$(MAKE) all --no-print-directory -C $(lex_dir)

lall:
	$(MAKE) all --no-print-directory -C $(lib_dir)

lclean:
	$(MAKE) clean --no-print-directory -C $(lib_dir)

lfclean:
	$(MAKE) fclean --no-print-directory -C $(lib_dir)

clean: lfclean
	$(MAKE) clean --no-print-directory -C $(main_dir)
	$(MAKE) clean --no-print-directory -C $(ft_readline_dir)
	$(MAKE) clean --no-print-directory -C $(lex_dir)

fclean: clean
	rm -rf $(name)

re: fclean all
