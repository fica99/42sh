/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/17 15:25:39 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	read_prompt(t_term *term)
{
	t_cord	*cord;
	t_buff	*buffer;

	cord = term->cord;
	set_start_cord(cord);
	term->history->history_index = double_arr_len(term->history->history_buff);
	buffer = term->buffer;
	if (!(buffer->buffer = ft_strnew(NORMAL_LINE)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
	set_input_mode(&(term->savetty));
	buffer->history_search = NULL;
	reading(buffer, cord, term->history);
	ft_memdel((void**)&(buffer->history_search));
	go_right(ft_strlen(buffer->buffer) - (cord->x_cur - cord->x_start +
			((cord->y_cur - cord->y_start) * cord->ws_col)), cord);
	reset_input_mode(&(g_term.savetty));
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(t_buff *buffer, t_cord *cord, t_history *history)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == '\n' || (*c == CTRL_C && !(g_flags & TERM_HIGHLIGHT)))
		{
			if (*c == CTRL_C)
				g_flags |= TERM_SIGINT;
			break ;
		}
		while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
				(unsigned)buffer->malloc_len)
			buffer->buffer = strnew_realloc_buf(buffer->buffer,
					buffer->malloc_len += NORMAL_LINE);
		if (!print_symbols(c, buffer, cord, history))
			if (!print_move(c, buffer, cord))
				print_read(c, buffer->buffer, cord);
		if ((g_flags & TERM_SIGINT) || (g_flags & TERM_EXIT))
			break ;
	}
}

void	read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode(&(g_term.savetty));
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}
