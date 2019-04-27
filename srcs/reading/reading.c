/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/28 00:13:07 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

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
