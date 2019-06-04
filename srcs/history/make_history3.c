/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/04 20:29:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    free_history(t_history **history)
{
	char    	**buf;

	buf = (*history)->history_buff;
	ft_memdel((void**)&((*history)->history_path));
	free_double_arr(buf);
	buf = NULL;
    ft_memdel((void**)history);
}

// void	find_history(void)
// {
// 	ft_putstr_fd(tigetstr("sc"), STDIN_FILENO);
// 	go_right(ft_strlen(g_term.buffer) - g_term.cord->x_cur - g_term.cord->x_start +
// 			((g_term.cord->y_cur - g_term.cord->y_start) * g_term.cord->ws_col), g_term.cord);
// 	ft_putstr_fd("\nHistory search: ",STDIN_FILENO);
// 	ft_putstr_fd(tigetstr("rc"), STDIN_FILENO);
// }