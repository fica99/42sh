/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 22:40:37 by aashara-         ###   ########.fr       */
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
		ft_putstr_fd("\033[", STDIN_FILENO);
		ft_putnbr_fd(i, STDIN_FILENO);
		ft_putchar_fd('D',STDIN_FILENO);
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
		go_to(g_term.x_cur);
	}
}

void	go_to(short i)
{
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(i, STDIN_FILENO);
	ft_putchar_fd('C',STDIN_FILENO);
}

void	go_right(void)
{
	if (g_term.x_cur >= g_term.ws_col - 1)
	{
		g_term.x_cur = -1;
		(g_term.y_cur)++;
		ft_putstr_fd(NEXT_LINE, STDIN_FILENO);
	}
	else
		ft_putstr_fd(RIGHT, STDIN_FILENO);
	(g_term.x_cur)++;
}
