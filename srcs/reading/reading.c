/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/11 02:09:49 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		read_prompt(t_term *term)
{
	set_input_mode(&g_raw_mode);
	init_terminfo();
	init_line(&g_line, term);
	reading(&g_line);
	autocomplite(NULL, NULL);
	if (g_line.buffer.buffer && *(g_line.buffer.buffer))
	{
		go_right(ft_strlen(g_line.buffer.buffer + g_line.cord->pos),
		g_line.cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
		{
			write_history(g_line.buffer.buffer, &term->history);
			term->buffer = ft_strdup(g_line.buffer.buffer);
		}
	}
	if (g_line.copy_buff.buffer)
		term->copy_line = ft_strdup(g_line.copy_buff.buffer);
	ft_putchar_fd('\n', STDIN_FILENO);
	free_line(&g_line, term);
	reset_terminfo();
	set_attr(&g_orig_mode);
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
			line->buffer.buffer = ft_strdup_realloc(line->buffer.buffer,
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
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}

void	reset_terminfo(void)
{
	char	*rmkx_mode;

	if ((rmkx_mode = tigetstr("rmkx")) != (char*)-1)
		ft_putstr_fd(rmkx_mode, STDIN_FILENO);
}

void	init_terminfo(void)
{
	char	*term;
	int		err;
	char	*smkx_mode;

	if ((term = ft_getenv("TERM")) == NULL ||
	(setupterm(term, STDIN_FILENO, &err) == ERR))
		print_error("42sh", "setupterm() error", NULL, 0);
	if ((smkx_mode = tigetstr("smkx")) != (char*)-1
		&& tigetstr("u7") != (char*)-1
	&& tigetstr("kcub1") != (char*)-1 && tigetstr("khome") != (char*)-1
	&& tigetstr("kcuf1") != (char*)-1 && tigetstr("kend") != (char*)-1
	&& tigetstr("cup") != (char*)-1 && tigetstr("sc") != (char*)-1
	&& tigetstr("rc") != (char*)-1 && tigetstr("ed") != (char*)-1
	&& tigetstr("clear") != (char*)-1 && tigetstr("kdch1") != (char*)-1
	&& tigetstr("kcuu1") != (char*)-1 && tigetstr("kcud1") != (char*)-1
	&& tigetstr("kLFT") != (char*)-1 && tigetstr("kRIT") != (char*)-1)
		ft_putstr_fd(smkx_mode, STDIN_FILENO);
	else
		print_error("42sh", "no correct capabilities", NULL, 0);
}
