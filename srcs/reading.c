/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/27 13:03:41 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include<stdio.h>

void	read_prompt(void)
{
	if (!(g_term.buffer = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	g_term.malloc_len = NORMAL_LINE;
	set_input_mode();
	reading();
	reset_input_mode();
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(void)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == CTRL_C || *c == '\n')
		{
			if (*c == CTRL_C)
				g_flags |= TERM_SIGINT;
			break;
		}
		while (ft_strlen(g_term.buffer) + ft_strlen(c) >= (unsigned)g_term.malloc_len)
			g_term.buffer = strnew_realloc_buf(g_term.buffer, g_term.malloc_len += NORMAL_LINE);
		print_read(c);
	}
}

void	read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}
void	print_read(char *c)
{
	short len;

	len = g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start) * g_term.ws_col);
	if ((!(ft_strcmp(c, LEFT)) || !(ft_strcmp(c, HOME))) && len)
		!(ft_strcmp(c, LEFT)) ? go_left(1) : go_left(len);
	else if ((!(ft_strcmp(c, RIGHT)) || !(ft_strcmp(c, END))) && ((short)ft_strlen(g_term.buffer) > len))
		!(ft_strcmp(c, RIGHT)) ? go_right(1) : go_right(ft_strlen(g_term.buffer) - len);
	//else if (*c == TAB)
		//autocom();
	else
		print_read_other(c);
}

void	print_read_other(char *c)
{
	short len;

	len = g_term.x_cur - g_term.x_start + ((g_term.y_cur - g_term.y_start) * g_term.ws_col);
	if (((*c == BCSP || *c == CTRL_H) && len) || !ft_strcmp(c, DEL) || *c == CTRL_D)
	{
		if (*c == BCSP || *c == CTRL_H)
		{
			go_left(1);
			len--;
		}
		if (!ft_strlen(g_term.buffer) && *c == CTRL_D)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		del_symb(g_term.buffer, len);
	}
	else if (ft_isprint(*c))
		print_symb(c, g_term.buffer, len);
}
