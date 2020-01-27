# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/26 18:28:13 by aashara-          #+#    #+#              #
#    Updated: 2020/01/26 19:06:58 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		jobs

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
SRC_FLS	=		launch_job.c\
				launch_process.c\
				red.c\
				get_fname.c\
				ft_pathcmp.c\
				make_redir.c\
				launch_builtin.c\
				hndl_chld.c\
				free_job.c\
				check_job.c\
				put_in.c\
				init_jobs.c\
				find_job.c\
				job_print.c\
				pipes_routine.c\
				signals.c\
				uniq_env.c

HDR_FLS =		jobs.h

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
HDRS	=		$(addprefix $(HDR_DIR)/, $(HDR_FLS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR) -I $(LDARHS_DIR) -I $(LDIRHS_DIR) \
				-I $(LHASHHS_DIR) -I $(LSTRHS_DIR) -I ../error/includes/ \
				-I ../environ/includes -I ../hash_table/includes/\
				-I ../lex/includes/ -I ../interpretator/includes/ -I ../interpretator/includes/\
				-I ../ft_readline/includes/ -I ../builtins/includes/
DFLGS	=		-MMD

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: $(NAME)

$(LFT_DIR)/$(LFT):
	$(MAKE) -C $(LFT_DIR)

$(LDIR_DIR)/$(LDIR):
	$(MAKE) -C $(LDIR_DIR)

$(LDAR_DIR)/$(LDAR):
	$(MAKE) -C $(LDAR_DIR)

$(LSTR_DIR)/$(LSTR):
	$(MAKE) -C $(LSTR_DIR)

$(LHASH_DIR)/$(LHASH):
	$(MAKE) -C $(LHASH_DIR)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(LFT_DIR)/$(LFT) $(LDAR_DIR)/$(LDAR) $(LDIR_DIR)/$(LDIR) $(LHASH_DIR)/$(LHASH) $(LSTR_DIR)/$(LSTR) $(OBJS)

clean:
	$(MAKE) -C $(LFT_DIR) clean
	$(MAKE) -C $(LDAR_DIR) clean
	$(MAKE) -C $(LDIR_DIR) clean
	$(MAKE) -C $(LSTR_DIR) clean
	$(MAKE) -C $(LHASH_DIR) clean
	$(RM) $(OBJ_DIR)

fclean:
	$(MAKE) -C $(LFT_DIR) fclean
	$(MAKE) -C $(LDIR_DIR) fclean
	$(MAKE) -C $(LDAR_DIR) fclean
	$(MAKE) -C $(LSTR_DIR) fclean
	$(MAKE) -C $(LHASH_DIR) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all
