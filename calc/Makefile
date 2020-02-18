# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 18:08:37 by aashara-          #+#    #+#              #
#    Updated: 2020/02/18 21:24:06 by ggrimes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		calc

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
SRC_FLS	=		calc_add_fun.c\
				calc.c\
				calc_lexer.c\
				calc_arr_tkns.c\
				calc_mul_fun.c\
				calc_inc_fun.c\
				calc_com_fun.c\
				calc_eq_fun.c\
				calc_log_fun.c\
				calc_tkn.c\
				calc_num_fun.c\
				calc_parent_fun.c\
				calc_error_fun.c\
				calc_var_fun.c\
				calc_var_tkn.c\
				calc_arr_reloc.c\
				calc_atoi.c\
				calc_ltoa.c\

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR) -I $(LDARHS_DIR) -I $(LDIRHS_DIR) \
				-I $(LHASHHS_DIR) -I $(LSTRHS_DIR) -I ../main/includes/
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
