/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 00:12:09 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include<stdio.h>

void	read_prompt(void)
{
	if (!(cord.buffer = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	cord.malloc_len = NORMAL_LINE;
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
		read_handler(c);
		if (g_flags)
		{
			if (g_flags & SHELL_SIGINT)
				ft_strclr(cord.buffer);
			g_flags &= ~SHELL_SIGINT;
			g_flags &= ~SHELL_SIGQUIT;
			g_flags &= ~SHELL_SIGWINCH;
		}
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(cord.buffer) + ft_strlen(c) >= (unsigned)cord.malloc_len)
			cord.buffer = strnew_realloc_buf(cord.buffer, cord.malloc_len += NORMAL_LINE);
		print_read(c);
	}
}

void	read_handler(char *c)
{
	short	nb;

	if ((nb = read(STDIN_FILENO, c, LINE_MAX)) < 0)
			print_error("minishell", "read() error", NULL, 0);
	c[nb] = '\0';
}

void	print_read(char *c)
{
	short	len;

	len = cord.x_cur - cord.prompt + (cord.y_cur * cord.ws_col);
	if (*c == CTRL_H)
		*c = BCSP;
	if (!(ft_strcmp(c, LEFT)) && len)
		go_left(1);
	else if (!(ft_strcmp(c, RIGHT)) && ((short)ft_strlen(cord.buffer) > len))
		go_right();
	else if (*c == TAB)
		while (!(autocom(&(cord.buffer), cord.malloc_len)))
			cord.buffer = strnew_realloc_buf(cord.buffer, cord.malloc_len += NORMAL_LINE);
	else
		print_read_other(c, len);
}

void	print_read_other(char *c, short len)
{
	if ((*c == BCSP && len) || !ft_strcmp(c, DEL) || *c == CTRL_D)
	{
		if (*c == BCSP)
		{
			go_left(1);
			len--;
		}
		if (!ft_strlen(cord.buffer) && *c == CTRL_D)
			exit(EXIT_SUCCESS);
		del_symb(cord.buffer, len);
	}
	else if (ft_isprint(*c) && *c != BCSP)
		print_symb(c, cord.buffer, len);
}
