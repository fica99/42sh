# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/22 15:12:37 by aashara-          #+#    #+#              #
#    Updated: 2020/01/26 18:05:58 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		ft_readline

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
SRC_FLS	=		add_to_history_buff.c\
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

HDR_FLS =		ft_readline.h\
				rl_templates.h

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
HDRS	=		$(addprefix $(HDR_DIR)/, $(HDR_FLS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -g
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR) -I $(LDARHS_DIR) -I $(LDIRHS_DIR) \
				-I $(LHASHHS_DIR) -I $(LSTRHS_DIR) -I ../error/includes/ \
				-I ../environ/includes
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
