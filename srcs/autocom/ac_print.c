/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olegmulko <olegmulko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:45:16 by olegmulko         #+#    #+#             */
/*   Updated: 2019/07/03 13:46:23 by olegmulko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ac_print_options(t_autocom *ac, t_cord *cord)
{
	int	i;
	int	j;


	if (!ac || !cord)
		return ;
	ac_return_carriage(ac->rows + 1);
	i = ac->index_print;
	move_cursor_up(ac->rows);
	while (ac->options[i])
	{
		j = -1;
		while (ac->options[i] && ++j < ac->rows)
		{
			if (i == ac->opts_print)
			break;
			if (i == ac->index && ac->first)
				ac_select_option(ac->options[i]);
			else
				ft_putstr_fd(ac->options[i], STDIN_FILENO);
			move_cursor_left((int)ft_strlen(ac->options[i++]));
			move_cursor_down(1);
		}
		if (i == ac->opts_print)
			break;
		move_cursor_up(ac->rows);
		move_cursor_right(ac->max_len + 1);
		}
	move_cursor_pos(cord->y_cur, cord->x_cur);
	ac->first = 1;
}

void	ac_select_option(char *option)
{
	ft_putstr_fd("\033[46m", STDIN_FILENO);
	ft_putstr_fd(option, STDIN_FILENO);
	ft_putstr_fd("\033[0m", STDIN_FILENO);
}

void	ac_clear_options()
{
	char	*esc;

	if (!(esc = tigetstr("ed"))) //обработать ошибки
		return ;
	ft_putstr_fd(esc, STDIN_FILENO);
}

void	ac_return_carriage(short count)
{
	char	*esc;
	short	i;

	if (!(esc = tigetstr("cud1"))) //обработать ошибки
		return ;
	i = -1;
	while(++i < count)
		ft_putstr_fd(esc, STDIN_FILENO);
}
