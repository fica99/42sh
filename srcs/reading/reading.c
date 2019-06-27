/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/28 00:04:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*read_prompt(t_term term)
{
	t_line	line;
	char	*buffer;

	g_term.line = line;
	line.cord = init_cord();
	get_win_size(line.cord);
	get_cur_cord(line.cord);
	set_start_cord(line.cord);
	line.copy_buff = term.copy_line;
	term.history->history_index = double_arr_len(term.history->history_buff);
	line.buffer = init_buff(line.buffer);
	line.save_buff = init_buff(line.save_buff);
	line.history_search = init_buff(line.history_search);
	set_input_mode(&(line.savetty));
	reading(line, term.history);
	if (!(buffer = ft_strdup(line.buffer.buffer)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	go_right(ft_strlen(buffer) - line.cord->pos, line.cord);
	ft_putchar_fd('\n', STDIN_FILENO);
	reset_input_mode(&(line.savetty));
	term.copy_line = line.copy_buff;
	ft_memdel((void**)&(line.save_buff.buffer));
	ft_memdel((void**)&(line.history_search.buffer));
	ft_memdel((void**)&(line.buffer.buffer));
	free_cord(&(line.cord));
	if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
		write_history(buffer, term.history);
	return (buffer);
}

void	reading(t_line line, t_history *history)
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
		while (ft_strlen(line.buffer.buffer) + ft_strlen(c) >=
				(unsigned)line.buffer.malloc_len)
			line.buffer.buffer = strnew_realloc_buf(line.buffer.buffer,
					line.buffer.malloc_len += NORMAL_LINE);
		if (*c == '\n' && !check_quotes(line))
			break ;
		if (!print_symbols(c, line, history))
			if (!print_move(c, line))
				print_printable(c, line.buffer.buffer, line.cord);
		if (g_flags & TERM_EXIT)
			break ;
	}
}

void	read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		go_right(ft_strlen(g_term.line.buffer.buffer) - g_term.line.cord->pos, g_term.line.cord);
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode(&(g_term.line.savetty));
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
