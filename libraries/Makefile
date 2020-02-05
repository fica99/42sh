# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 11:46:19 by olegmulko         #+#    #+#              #
#    Updated: 2020/02/03 19:34:40 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

libft := libft

libstr := libstr

libdir := libdir

libdar := libdar

libhash := libhash

.PHONY: all clean fclean $(libft) $(libstr) $(libdir) $(libdar) $(libhash)

all: $(libft) $(libstr) $(libdir) $(libdar) $(libhash)

$(libft):
	@$(MAKE) --no-print-directory -C $(libft)

$(libstr):
	@$(MAKE) --no-print-directory -C $(libstr)

$(libdir):
	@$(MAKE) --no-print-directory -C $(libdir)

$(libdar):
	@$(MAKE) --no-print-directory -C $(libdar)

$(libhash):
	@$(MAKE) --no-print-directory -C $(libhash)

clean:
	@$(MAKE) clean --no-print-directory -C  $(libft)
	@$(MAKE) clean --no-print-directory -C  $(libstr)
	@$(MAKE) clean --no-print-directory -C  $(libdir)
	@$(MAKE) clean --no-print-directory -C  $(libdar)
	@$(MAKE) clean --no-print-directory -C  $(libhash)

fclean:
	@$(MAKE) fclean --no-print-directory -C  $(libft)
	@$(MAKE) fclean --no-print-directory -C  $(libstr)
	@$(MAKE) fclean --no-print-directory -C  $(libdir)
	@$(MAKE) fclean --no-print-directory -C  $(libdar)
	@$(MAKE) fclean --no-print-directory -C  $(libhash)

re: fclean all
