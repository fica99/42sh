# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 13:57:06 by aashara-          #+#    #+#              #
#    Updated: 2020/02/03 16:15:38 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		libdar.a

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		srcs
HDR_DIR	=		includes
OBJ_DIR	=		objs

# ------------  LIBFT  ------------------------------------------------------- #
LFT_DIR	=		../libft
LHS_DIR	=		$(LFT_DIR)/includes

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=		ft_check_exec.c\
				ft_dar_add.c\
				ft_darlen.c\
				ft_free_dar.c\
				ft_dardup.c\
				ft_darnew.c\
				ft_putdar.c\
				ft_putdar_fd.c\
				ft_dar2str.c\
				ft_darjoin.c\
				ft_dar_sort.c\

HDR_FLS =		libdar.h

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
HDRS	=		$(addprefix $(HDR_DIR)/, $(HDR_FLS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR)
DFLGS	=		-MMD -MP

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: $(NAME)

-include $(DEPS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS) | $(OBJ_DIR)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
