# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 12:59:55 by aashara-          #+#    #+#              #
#    Updated: 2019/03/15 14:28:56 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC=srcs/reading.c\
	srcs/flags.c\
	srcs/check2.c\
	srcs/check.c\
	srcs/make.c\
	srcs/check3.c\
	srcs/output.c\
	srcs/sort_list.c\
	srcs/sort_list2.c\
	srcs/print_rows.c\
	srcs/print_rows2.c\
	srcs/check4.c\
	srcs/print_rows3.c\
	srcs/print_cols.c\
	srcs/print_cols2.c\

INCLUDES=includes

EXTRA_FLAGS=-Wall -Wextra -Werror

LIB=libft

all: $(NAME)

$(NAME):
			@make re -C $(LIB)
			@gcc $(EXTRA_FLAGS) -o $(NAME) main.c $(SRC) -I libft/includes -I $(INCLUDES) -L $(LIB) -lft

clean:
			@make clean -C $(LIB)

fclean: clean
			@make fclean -C $(LIB)
			@rm -f $(NAME)

re: fclean all