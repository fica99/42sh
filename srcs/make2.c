/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/24 17:40:49 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*strnew_realloc_buf(char *str, short len)
{
	char	*arr;

	arr = str;
	if (!(str = ft_strnew(len)))
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	}
	str = ft_strcat(str, arr);
	ft_memdel((void**)&arr);
	return (str);
}

void	reset_input_mode (void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(g_term.savetty)) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}

void	go_left(short i)
{
	short	change;

	if (g_term.x_cur - i >= 0)
	{
		g_term.x_cur -= i;
		GO_LEFT(i);
	}
	else
	{
		change = g_term.x_cur;
		while (change < i)
		{
			change += g_term.ws_col;
			ft_putstr_fd(PREV_LINE, STDIN_FILENO);
			g_term.y_cur--;
		}
		g_term.x_cur = change - i;
		GO_RIGHT(g_term.x_cur);
	}
}

void	go_right(short i)
{
	short change;

	if (g_term.x_cur + i >= g_term.ws_col)
	{
		change = g_term.x_cur;
		while (change < g_term.x_cur + i)
		{
			change += g_term.ws_col;
			ft_putstr_fd(NEXT_LINE, STDIN_FILENO);
			g_term.y_cur++;
		}
		change = (g_term.x_cur + i) % g_term.ws_col;
		g_term.x_cur = 0;
		if (change)
			go_right(change);
	}
	else
	{
		GO_RIGHT(i);
		g_term.x_cur += i;
	}
}
