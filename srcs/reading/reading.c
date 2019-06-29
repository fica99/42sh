/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/29 10:44:48 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*read_prompt(t_term term)
{
	char	*buffer;

	term.line.cord = init_cord();
	get_win_size(term.line.cord);
	get_cur_cord(term.line.cord);
	set_start_cord(term.line.cord);
	term.line.copy_buff = term.copy_line;
	term.history->history_index = double_arr_len(term.history->history_buff);
	term.line.buffer = init_buff(term.line.buffer);
	term.line.save_buff = init_buff(term.line.save_buff);
	term.line.history_search = init_buff(term.line.history_search);
	set_input_mode(&(term.line.savetty));
	reading(term.line, term.history);
	if (!(buffer = ft_strdup(term.line.buffer.buffer)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	go_right(ft_strlen(buffer) - term.line.cord->pos, term.line.cord);
	ft_putchar_fd('\n', STDIN_FILENO);
	reset_input_mode(&(term.line.savetty));
	term.copy_line = term.line.copy_buff;
	ft_memdel((void**)&(term.line.save_buff.buffer));
	ft_memdel((void**)&(term.line.history_search.buffer));
	ft_memdel((void**)&(term.line.buffer.buffer));
	free_cord(&(term.line.cord));
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
			if (!print_move(c, line.buffer.buffer, line.cord))
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
