# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2020/02/03 23:07:41 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name := 42sh

lib_dir := libraries

main_dir := main

ft_readline_dir := ft_readline

cc := gcc

lib_flags := -L libraries/libft -L libraries/libdir -L libraries/libdar\
			-L libraries/libhash -L libraries/libstr -lft -ldir -ldar -lstr -lhash -lncurses

srcs_dir := srcs

srcs := $(wildcard $(main_dir)/$(srcs_dir)/*.c)\
		$(wildcard $(ft_readline_dir)/$(srcs_dir)/*.c)

objs_dir := objs

objs := $(patsubst $(main_dir)/$(srcs_dir)/%.c,$(main_dir)/$(objs_dir)/%.o, $(srcs))

objs := $(patsubst $(ft_readline_dir)/$(srcs_dir)/%.c,$(ft_readline_dir)/$(objs_dir)/%.o, $(objs))


.PHONY: all lall lclean lfclean clean fclean re $(main_dir) $(ft_readline_dir)

all: lall $(main_dir) $(ft_readline_dir) $(name)

$(name): $(objs)
	$(cc) $(objs) -o $(name) $(lib_flags)

$(main_dir):
	$(MAKE) all --no-print-directory -C $(main_dir)

$(ft_readline_dir):
	$(MAKE) all --no-print-directory -C $(ft_readline_dir)

lall:
	$(MAKE) all --no-print-directory -C $(lib_dir)

lclean:
	$(MAKE) clean --no-print-directory -C $(lib_dir)

lfclean:
	$(MAKE) fclean --no-print-directory -C $(lib_dir)

clean: lfclean
	$(MAKE) clean --no-print-directory -C $(main_dir)
	$(MAKE) clean --no-print-directory -C $(ft_readline_dir)

fclean: clean
	rm -rf $(name)

re: fclean all
