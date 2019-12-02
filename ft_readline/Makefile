# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2019/12/01 22:32:52 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := rl_main.c\
	rl_free.c\
	rl_init.c\
	rl_prompt.c\
	rl_read_mode.c\
	rl_reading.c\
	rl_init_hash.c\
	rl_cord.c\
	rl_print.c\
	rl_check.c\
	rl_k_cur_left.c\
	rl_cur_movements.c\
	rl_k_cur_right.c\
	rl_k_other.c\
	rl_history.c\
	rl_k_history.c\
	rl_signal.c\
	rl_prompt_time.c\
	rl_k_history_search.c\
	rl_k_emacs.c\
	rl_str.c\
	rl_k_cut_copy_paste.c\
	rl_k_emacs2.c\
	rl_k_vi.c\
	rl_k_vi2.c\
	rl_k_vi3.c\
	rl_init_hash2.c\
	rl_k_vi4.c\
	rl_k_vi5.c\
	rl_init_history.c\
	rl_hist_expansions.c\
	rl_err.c\
	rl_main2.c\

objs := $(srcs:.c=.o)

srcs_dir := srcs

objs_dir := objs

inc_dir := includes

lib_dir := ../libraries

objects := $(addprefix $(objs_dir)/, $(objs))

sources := $(addprefix $(srcs_dir)/, $(srcs))

header := $(addprefix $(inc_dir)/, ft_readline.h) $(addprefix $(inc_dir)/, rl_colours.h)\
$(addprefix $(inc_dir)/, rl_errors.h) $(addprefix $(inc_dir)/, rl_templates.h)

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_libdir := $(addprefix $(addprefix $(lib_dir)/, libdir/), includes)

includes_flags := -I $(inc_dir) -I $(includes_libft) -I $(includes_libhash) -I $(includes_libstr)\
-I $(includes_libdar) -I $(includes_libdir)

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
