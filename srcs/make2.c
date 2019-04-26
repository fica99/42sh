/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/26 21:01:23 by filip            ###   ########.fr       */
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
	g_term.x_cur -= i;
	while (g_term.x_cur <= 0)
	{
		g_term.x_cur += g_term.ws_col;
		g_term.y_cur--;
	}
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(g_term.y_cur, STDIN_FILENO);
	ft_putchar_fd(';', STDIN_FILENO);
	ft_putnbr_fd(g_term.x_cur, STDIN_FILENO);
	ft_putchar_fd('H', STDIN_FILENO);
}

void	go_right(short i)
{
	g_term.x_cur += i;
	while (g_term.x_cur > g_term.ws_col)
	{
		g_term.x_cur -= g_term.ws_col;
		g_term.y_cur++;
	}
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(g_term.y_cur, STDIN_FILENO);
	ft_putchar_fd(';', STDIN_FILENO);
	ft_putnbr_fd(g_term.x_cur, STDIN_FILENO);
	ft_putchar_fd('H', STDIN_FILENO);
}
