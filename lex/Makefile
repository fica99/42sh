# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2020/01/30 22:08:28 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		lex

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
SRC_FLS	=		lex_lexer.c\
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
				lex_str.c\
				lex_double_quotes.c\
				lex_single_quotes.c\
				lex_back_quotes.c\
				lex_ctrl_c.c\
				lex_cs_inc_dec.c\
				lex_cs_open_close.c\
				lex_cs_filter.c\
				lex_cs.c\
				lex_val_tkn_processing.c\
				lex_debug.c\

HDR_FLS =		lex.h

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
				-I $(LHASHHS_DIR) -I $(LSTRHS_DIR) -I ../ft_readline/includes/ \
				-I ../environ/includes -I ../error/includes
DFLGS	=		-MMD

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean

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
	$(RM) $(OBJ_DIR)
