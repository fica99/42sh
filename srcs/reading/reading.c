/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/03 15:52:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		read_prompt(t_term *term)
{
	g_line.copy_buff.buffer = term->copy_line;
	g_line.copy_buff.malloc_len = ft_strlen(term->copy_line);
	init_line(&g_line);
	g_line.history = term->history;
	g_line.history.history_index = double_arr_len(g_line.history.history_buff);
	set_input_mode(&(g_line.savetty));
	reading(&g_line);
	if (g_line.buffer.buffer && *(g_line.buffer.buffer))
	{
		go_right(ft_strlen(g_line.buffer.buffer + g_line.cord->pos),
		g_line.cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
		{
			write_history(g_line.buffer.buffer, &term->history);
			if (!(term->buffer = ft_strdup(g_line.buffer.buffer)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
		}
	}
	if (g_line.copy_buff.buffer)
		if (!(term->copy_line = ft_strdup(g_line.copy_buff.buffer)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
	ft_putchar_fd('\n', STDIN_FILENO);
	reset_input_mode(&(g_line.savetty));
	free_line(&g_line, term);
}

void		reading(t_line *line)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if ((*c == CTRL_C && !(g_flags & TERM_HIGHLIGHT)))
		{
			g_flags |= TERM_SIGINT;
			break ;
		}
		while (ft_strlen(line->buffer.buffer) + ft_strlen(c) >=
				(unsigned)line->buffer.malloc_len)
			line->buffer.buffer = strnew_realloc_buf(line->buffer.buffer,
					line->buffer.malloc_len += NORMAL_LINE);
		if (*c == '\n' && !check_quotes(line))
			break ;
		if (!print_symbols(c, line))
			if (!print_move(c, line->buffer.buffer, line->cord))
				print_printable(c, line->buffer.buffer, line->cord);
		if (g_flags & TERM_EXIT)
			break ;
	}
}

void		read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		go_right(ft_strlen(g_line.buffer.buffer) - g_line.cord->pos,
		g_line.cord);
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode(&(g_line.savetty));
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}

void		set_input_mode(struct termios *savetty)
{
	struct termios	tty;

	if (!isatty(0))
		print_error("42sh", "stdin not terminal\n", NULL, 0);
	if (tcgetattr(STDIN_FILENO, savetty) < 0)
		print_error("42sh", "tcgetattr() error", NULL, 0);
	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		print_error("42sh", "tcgetattr() error", NULL, 0);
	tty.c_lflag &= ~(ICANON | ECHO | ISIG);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
		print_error("42sh", "tcsetattr() error", NULL, 0);
}

void		reset_input_mode(struct termios *savetty)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, savetty) < 0)
		print_error("42sh", "tcsetattr() error", NULL, 0);
}
