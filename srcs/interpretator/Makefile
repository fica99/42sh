# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2019/10/18 19:49:28 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

srcs := interpretator.c\
		rredir.c\
		lredir.c\
		pipes.c\
		dup_fd.c\
		exec.c\
		spec_symb.c\
		parse_quotes.c\
		aggr_fd.c\
		process.c\

obj_files := $(srcs:.c=.o)

obj_dir := obj

objects := $(addprefix $(obj_dir)/, $(obj_files))

inc_dir := ../../includes/interpretator

lib_dir := ../../libraries

includes_libft := $(addprefix $(addprefix $(lib_dir)/, libft/), includes)

includes_libstr := $(addprefix $(addprefix $(lib_dir)/, libstr/), includes)

includes_libdir := $(addprefix $(addprefix $(lib_dir)/, libdir/), includes)

includes_libdar := $(addprefix $(addprefix $(lib_dir)/, libdar/), includes)

includes_libstack := $(addprefix $(addprefix $(lib_dir)/, libstack/), includes)

includes_libfifo := $(addprefix $(addprefix $(lib_dir)/, libfifo/), includes)

includes_libhash := $(addprefix $(addprefix $(lib_dir)/, libhash/), includes)

includes := -I $(inc_dir) -I $(includes_libdar) -I $(includes_libdir) \
	-I $(includes_libfifo) -I $(includes_libft) -I $(includes_libstack) -I $(includes_libstr) -I $(includes_libhash)

header := ../../includes/interpretator/interpretator.h

cc := gcc

cflags := -Wall -Wextra -Werror

all: $(obj_dir) $(objects)

$(obj_dir):
	@echo "\033[32m\033[1m--->Create object directory $(CURDIR)/$@\033[0m"
	@mkdir -p $@
	@$(MAKE) --no-print-directory objs

objs:
	@echo "\033[32m\033[1m--->Compile sources:\033[0m"
	@$(MAKE) --no-print-directory $(objects)

$(obj_dir)/%.o: %.c $(header)
	@echo "\033[31m\033[1m--->Create object file $(CURDIR)/$@\033[0m"
	@$(cc) $(cflags) $(includes) -o $@ -c $<

clean:
	@-rm -rf $(obj_dir)
	@echo "\033[36m\033[1m--->Remove $(CURDIR)/$(obj_dir)\033[0m"

re:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory all

