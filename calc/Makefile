# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2019/11/21 20:20:57 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := calc.c\
		calc_lexer.c\
		calc_debug.c\
		calc_add_fun.c\
		calc_mul_fun.c\
		calc_inc_fun.c\
		calc_com_fun.c\
		calc_eq_fun.c\
		calc_log_fun.c\
		calc_var_fun.c\

objs := $(srcs:.c=.o)

srcs_dir := srcs

objs_dir := objs

inc_dir := includes

lib_dir := ../libraries

objects := $(addprefix $(objs_dir)/, $(objs))

sources := $(addprefix $(srcs_dir)/, $(srcs))

header := $(addprefix $(inc_dir)/, calc.h)

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_flags := -I $(inc_dir) -I $(includes_libft) -I $(includes_libhash) -I $(includes_libstr)\
-I $(includes_libdar)

cc := gcc

cflags := -Wall -Wextra -Werror -g -O0

.PHONY: all compilation clean re

all: $(objs_dir) $(objects)
	@echo "\033[32mFinish ft_readline compilation\033[0m"

$(objs_dir):
	@mkdir -p $@
	@$(MAKE) --no-print-directory compilation

compilation:
	@$(MAKE) --no-print-directory $(objects)

$(objs_dir)/%.o: $(srcs_dir)/%.c $(header)
	@$(cc) $(cflags) $(includes_flags) -o $@ -c $<

clean:
	@-rm -rf $(objs_dir)
	@echo "\033[31mRemove $(CURDIR)/$(objs_dir)\033[0m"

re:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory all