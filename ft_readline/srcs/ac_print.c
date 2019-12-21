/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:45:16 by olegmulko         #+#    #+#             */
/*   Updated: 2019/12/21 18:16:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ac_print_options(t_autocom *ac, t_rl_cord *cord)
{
	int	i;

	if (!ac || !cord)
		return ;
	ac_return_carriage(ac->rows + 1);
	i = ac->index_print;
	move_cursor_up(ac->rows);
	while (ac->options[i])
	{
		ac_print_coll(ac, &i);
		if (i == ac->opts_print)
			break ;
		move_cursor_up(ac->rows);
		move_cursor_right(ac->max_len + 1);
	}
	move_cursor_pos(cord->y_cur, cord->x_cur);
	ac->first = 1;
}

void	ac_print_coll(t_autocom *ac, int *index)
{
	int	j;

	j = -1;
	while (ac->options[*index] && ++j < ac->rows)
	{
		if (*index == ac->opts_print)
			break ;
		if (*index == ac->index && ac->first)
			ac_select_option(ac->options[*index]);
		else
			ft_putstr_fd(ac->options[*index], STDIN_FILENO);
		move_cursor_left((int)ft_strlen(ac->options[(*index)++]));
		move_cursor_down(1);
	}
}

void	ac_select_option(char *option)
{
	ft_putstr_fd("\033[46m", STDIN_FILENO);
	ft_putstr_fd(option, STDIN_FILENO);
	ft_putstr_fd("\033[0m", STDIN_FILENO);
}

void	ac_clear_options(void)
{
	char	*esc;

	if (!(esc = tigetstr("ed")))
		return ;
	ft_putstr_fd(esc, STDIN_FILENO);
}

void	ac_return_carriage(short count)
{
	char	*esc;
	short	i;

	if (!(esc = tigetstr("cud1")))
		return ;
	i = -1;
	while (++i < count)
		ft_putstr_fd(esc, STDIN_FILENO);
}
