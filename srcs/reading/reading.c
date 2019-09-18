/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 20:57:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		read_prompt(t_term *term)
{
	set_input_mode(&g_raw_mode);
	transmit_mode();
	set_cord(g_line.cord);
	reading(&g_line);
	autocomplite(NULL, NULL);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
	{
		write_hered(&g_line.buffer.buffer);
		if (g_line.buffer.buffer && *(g_line.buffer.buffer))
		{
			write_history(g_line.buffer.buffer, &term->history);
			if (!(term->buffer = ft_strdup(g_line.buffer.buffer)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	unset_data(&g_line);
	reset_transmit_mode();
	set_attr(&g_orig_mode);
}

void		reading(t_line *line)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if ((*c == CTRL_C && !(g_line_flags & TERM_HIGHLIGHT)))
		{
			g_flags |= TERM_SIGINT;
			break ;
		}
		check_malloc_len_buffer(&(line->buffer), c);
		check_new_line(line, c);
		if (g_line_flags & BREAK_FLAG)
			break;
		check_symbol(c, line);
		if ((g_flags & TERM_EXIT) || (g_line_flags & BREAK_FLAG))
			break ;
	}
	go_right(ft_strlen(line->buffer.buffer + line->cord->pos),
	line->cord);
}

void		read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		go_right(ft_strlen(g_line.buffer.buffer) - g_line.cord->pos,
		g_line.cord);
		ft_putchar_fd(NEW_LINE, STDERR_FILENO);
		err_exit("42sh", "read() error", NULL, NOERROR);
	}
	c[nb] = '\0';
}

void	transmit_mode(void)
{
	ft_putstr_fd(TRANSMIT_MODE, STDIN_FILENO);
}

void	reset_transmit_mode(void)
{
	ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
}
