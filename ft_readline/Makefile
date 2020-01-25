# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/22 15:12:37 by aashara-          #+#    #+#              #
#    Updated: 2020/01/22 14:58:21 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := add_to_history_buff.c\
		free_readline.c\
		ft_readline.c\
		init_readline.c\
		rl_check.c\
		rl_cord.c\
		rl_cur_mov.c\
		rl_err.c\
		rl_free_history.c\
		rl_init_emacs_temp.c\
		rl_init_history.c\
		rl_init_structs.c\
		rl_init_temp.c\
		rl_init_vi_temp.c\
		rl_k_cur_left.c\
		rl_k_cur_right.c\
		rl_k_cut_copy_paste.c\
		rl_k_emacs.c\
		rl_k_emacs2.c\
		rl_k_history.c\
		rl_k_history_search.c\
		rl_k_other.c\
		rl_k_vi.c\
		rl_k_vi2.c\
		rl_k_vi3.c\
		rl_k_vi4.c\
		rl_k_vi5.c\
		rl_print.c\
		rl_prompt.c\
		rl_prompt_time.c\
		rl_str.c\
		rl_term_mode.c\
		history_exp.c\
		rl_k_tab.c\
		rl_autocom_print.c\
		rl_autocom_parse.c\
		rl_autocom_path.c\
		rl_autocom_bin.c\

objs := $(srcs:.c=.o)

srcs_dir := srcs

objs_dir := objs

inc_dir := includes

lib_dir := ../libraries

objects := $(addprefix $(objs_dir)/, $(objs))

sources := $(addprefix $(srcs_dir)/, $(srcs))

headers := $(addprefix $(inc_dir)/, ft_readline.h)\
			$(addprefix $(inc_dir)/, rl_templates.h)\

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_libdir := $(addprefix $(addprefix $(lib_dir)/, libdir/), includes)

includes_flags := -I $(includes_libft)\
				-I $(includes_libhash)\
				-I $(includes_libdar)\
				-I $(includes_libstr)\
				-I $(includes_libdir)\
				-I $(inc_dir)\

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

$(objs_dir)/%.o: $(srcs_dir)/%.c $(headers)
	@$(cc) $(cflags) $(includes_flags) -o $@ -c $<

clean:
	@-rm -rf $(objs_dir)
	@echo "\033[31mRemove $(CURDIR)/$(objs_dir)\033[0m"

re:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory all
