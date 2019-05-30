/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/30 15:04:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	read_prompt(void)
{
	get_cur_cord();
	g_term.x_start = g_term.x_cur;
	g_term.y_start = g_term.y_cur;
	if (!(g_term.buffer = ft_strnew(NORMAL_LINE)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	g_term.malloc_len = NORMAL_LINE;
	set_input_mode();
	reading();
	go_right(ft_strlen(g_term.buffer) - g_term.x_cur - g_term.x_start +
			((g_term.y_cur - g_term.y_start) * g_term.ws_col));
	change_buf();
	reset_input_mode();
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(void)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == '\n')
			break;
		if (*c == CTRL_C)
		{
			g_flags |= TERM_SIGINT;
			return ;
		}
		while (ft_strlen(g_term.buffer) + ft_strlen(c) >=
				(unsigned)g_term.malloc_len)
			g_term.buffer = strnew_realloc_buf(g_term.buffer,
					g_term.malloc_len += NORMAL_LINE);
		print_read(c);
		if (g_flags & TERM_EXIT)
			break ;
	}
}

void	read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}
