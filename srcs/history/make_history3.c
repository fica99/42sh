/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/31 22:12:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    free_history(void)
{
   char    	**buf;
	t_history	*history;

	buf = g_term.history->history_buff;
	history = g_term.history;
	free_double_arr(buf);
    ft_memdel((void**)&history);
}

void	find_history(void)
{
	ft_putstr_fd(tigetstr("sc"), STDIN_FILENO);
	go_right(ft_strlen(g_term.buffer) - g_term.x_cur - g_term.x_start +
			((g_term.y_cur - g_term.y_start) * g_term.ws_col));
	ft_putstr_fd("\nHistory search: ",STDIN_FILENO);
	ft_putstr_fd(tigetstr("rc"), STDIN_FILENO);
}