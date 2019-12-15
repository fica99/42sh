# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := parse.c\
		err.c\
		token_handle.c\
		close_fds.c\
		add_process.c\
		fd_aggr.c\
		word_list.c\
		ft_free_jobs.c\
		heredoc.c\
		ft_open.c\
		io_redir.c\
		add_redir.c\
		exec_jobs.c

objs := $(srcs:.c=.o)

srcs_dir := srcs

objs_dir := objs

inc_dir := includes

main_inc_dir := ../includes

lib_dir := ../libraries

objects := $(addprefix $(objs_dir)/, $(objs))

sources := $(addprefix $(srcs_dir)/, $(srcs))

header := $(addprefix $(inc_dir)/, interpretator.h)

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdir := $(addprefix $(addprefix $(lib_dir)/, libdir/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_libstack := $(addprefix $(addprefix $(lib_dir)/, libstack/), includes)

includes_libfifo := $(addprefix $(addprefix $(lib_dir)/, libfifo/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

includes_flags := -I $(inc_dir) -I $(main_inc_dir) -I $(includes_libdar) -I $(includes_libdir) \
	-I $(includes_libfifo) -I $(includes_libft) -I $(includes_libstack) -I $(includes_libstr) -I $(includes_libhash)

cc := gcc

cflags := -Wall -Wextra -Werror -g

.PHONY: all compilation clean re

all: $(objs_dir) $(objects)
	@echo "\033[32mFinish interpretator compilation\033[0m"

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
