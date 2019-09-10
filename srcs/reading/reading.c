/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/09 23:05:06 by aashara-         ###   ########.fr       */
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
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
		{
			write_history(g_line.buffer.buffer, &term->history);
			if (!(term->buffer = ft_strdup(g_line.buffer.buffer)))
				print_error("42sh", "malloc() error", NULL, ENOMEM);
			check_exist_hered(&term->buffer);
		}
	}
	if (g_line.copy_buff.buffer)
		if (!(term->copy_line = ft_strdup(g_line.copy_buff.buffer)))
			print_error("42sh", "malloc() error", NULL, ENOMEM);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
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
		if ((*c == CTRL_C && !(g_line_flags & TERM_HIGHLIGHT)))
		{
			g_flags |= TERM_SIGINT;
			break ;
		}
		check_malloc_len_buffer(&(line->buffer), c);
		check_new_line(line, c);
		if (g_line_flags & BREAK_FLAG)
			break;
		if (!print_symbols(c, line))
			if (!print_move(c, line->buffer.buffer, line->cord))
				print_printable(c, line->buffer.buffer, line->cord);
		if ((g_flags & TERM_EXIT) || (g_line_flags & BREAK_FLAG))
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
		ft_putchar_fd(NEW_LINE, STDERR_FILENO);
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}

void	reset_terminfo(void)
{
	char	*rmkx_mode;

	if ((rmkx_mode = STOP_TRANSMIT_MODE) != (char*)-1)
		ft_putstr_fd(rmkx_mode, STDIN_FILENO);
}

void	init_terminfo(void)
{
	char	*smkx_mode;

	if ((smkx_mode = TRANSMIT_MODE) != (char*)-1
		&& CUR_CORD != (char*)-1
	&& K_LFT != (char*)-1 && K_HOME != (char*)-1
	&& K_RGHT != (char*)-1 && K_END != (char*)-1
	&& SET_CUR != (char*)-1 && SAVE_CUR != (char*)-1
	&& RESTORE_CUR != (char*)-1 && CLEAR_END_SCREEN != (char*)-1
	&& CLEAR_SCREEN != (char*)-1 && K_DEL != (char*)-1
	&& K_UP != (char*)-1 && K_DOWN != (char*)-1
	&& SHIFT_LFT != (char*)-1 && SHIFT_RGHT != (char*)-1)
		ft_putstr_fd(smkx_mode, STDIN_FILENO);
	else
		print_error("42sh", "no correct capabilities", NULL, 0);
}
