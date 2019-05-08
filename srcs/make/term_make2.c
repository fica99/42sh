/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:56:18 by filip             #+#    #+#             */
/*   Updated: 2019/05/08 19:25:40 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void    ft_putstr_cord(char *str)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		(g_term.x_cur)++;
		str++;
		if (g_term.x_cur > g_term.ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			g_term.x_cur = 1;
			if (g_term.y_cur >= g_term.ws_row)
				(g_term.y_start)--;
			else
				(g_term.y_cur)++;
		}
	}
}

void	reset_term()
{
	char	*rmkx_mode;

	if ((rmkx_mode = tigetstr("rmkx")) != (char*)-1)
		tputs(rmkx_mode, 1, putchar);
	reset_shell_mode();
}