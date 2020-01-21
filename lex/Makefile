# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2020/01/21 21:04:34 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := lex_lexer.c\
		lex_tkn.c\
		lex_tkns.c\
		lex_get_tkn.c\
		lex_check_tkn.c\
		lex_check_or.c\
		lex_tkn_type.c\
		lex_tkn_class.c\
		lex_check_greater.c\
		lex_check_less.c\
		lex_check_sep.c\
		lex_quotation_marks.c\
		lex_io_num.c\
		lex_asig_name.c\
		lex_dol.c\
		lex_con_sub.c\
		lex_log_opers.c\
		lex_check_and.c\
		lex_check_fig_brace.c\
		lex_arithmetic_opers.c\
		lex_str.c\
		lex_double_quotes.c\
		lex_single_quotes.c\
		lex_back_quotes.c\
		lex_debug.c\

objs := $(srcs:.c=.o)

srcs_dir := srcs

objs_dir := objs

inc_dir := includes

lib_dir := ../libraries

objects := $(addprefix $(objs_dir)/, $(objs))

sources := $(addprefix $(srcs_dir)/, $(srcs))

header := $(addprefix $(inc_dir)/, lex.h)

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
	@echo "\033[32mFinish lexer compilation\033[0m"

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
