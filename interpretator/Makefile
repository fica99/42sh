# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/04 20:28:45 by aashara-          #+#    #+#              #
#    Updated: 2020/02/20 01:48:05 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		interpretator

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		srcs
HDR_DIR	=		includes
OBJ_DIR	=		objs
LIB_DIR =		../libraries

# ------------  LIBFT  ------------------------------------------------------- #
LFT		=		libft.a
LFT_DIR	=		$(LIB_DIR)/libft
LHS_DIR	=		$(LFT_DIR)/includes

# ------------  LIBDAR  ------------------------------------------------------- #
LDAR		=		libdar.a
LDAR_DIR	=		$(LIB_DIR)/libdar
LDARHS_DIR	=		$(LDAR_DIR)/includes

# ------------  LIBDIR  ------------------------------------------------------- #
LDIR		=		libdir.a
LDIR_DIR	=		$(LIB_DIR)/libdir
LDIRHS_DIR	=		$(LDIR_DIR)/includes

# ------------  LIBHASH  ------------------------------------------------------- #
LHASH		=		libhash.a
LHASH_DIR	=		$(LIB_DIR)/libhash
LHASHHS_DIR	=		$(LHASH_DIR)/includes

# ------------  LIBSTR  ------------------------------------------------------- #
LSTR		=		libstr.a
LSTR_DIR	=		$(LIB_DIR)/libstr
LSTRHS_DIR	=		$(LSTR_DIR)/includes

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=			add_redir.c\
					check_job.c\
					exec_jobs.c\
					fd_aggr.c\
					ft_open.c\
					get_fname.c\
					heredoc.c\
					hndl_chld.c\
					io_redir.c\
					launch_builtin.c\
					launch_job.c\
					launch_process.c\
					make_redir.c\
					pipes_routine.c\
					put_in.c\
					uniq_env.c\
					init_jobs.c\
					find_in_path.c\
					chld_signals.c\
					tilda_substitutions.c\
					vars_substitutions.c\
					cut_quotes.c\
					escaping_characters.c\
					substitutions.c\
					pattern_substitutions.c\
					expansions_implementation.c\
					expr_validation.c\
					clean_proc.c\
					arithmetic_operation.c\

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR) -I $(LDARHS_DIR) -I $(LDIRHS_DIR) \
				-I $(LHASHHS_DIR) -I $(LSTRHS_DIR) -I ../ft_readline/includes/ \
				-I ../lex/includes/ -I ../parser/includes/ -I ../main/includes \
				-I ../calc/includes/
DFLGS	=		-MMD -MP

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean

all: $(NAME)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)

clean:
	$(RM) $(OBJ_DIR)
