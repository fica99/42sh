/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/07 16:07:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	read_prompt(t_term *term)
{
	t_cord	*cord;
	char	*buffer;
	short	malloc_len;

	cord = term->cord;
	get_cur_cord(cord);
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
	if (!(buffer = ft_strnew(NORMAL_LINE)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	malloc_len = NORMAL_LINE;
	set_input_mode(&(term->savetty));
	reading(&buffer, &malloc_len, cord, term->history);
	change_buf(term->history, &buffer);
	go_right(ft_strlen(buffer) - cord->x_cur - cord->x_start +
			((cord->y_cur - cord->y_start) * cord->ws_col), cord);
	reset_input_mode(&(g_term.savetty));
	term->buffer = buffer;
	term->malloc_len = malloc_len;
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(char **buffer, short *malloc_len, t_cord *cord, t_history *history)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == '\n' || *c == CTRL_C)
		{
			if (*c == CTRL_C)
				g_flags |= TERM_SIGINT;
			break ;
		}
		while (ft_strlen(*buffer) + ft_strlen(c) >=
				(unsigned)*malloc_len)
			*buffer = strnew_realloc_buf(*buffer,
					*malloc_len += NORMAL_LINE);
		print_read(c, *buffer, cord, history);
		if (g_flags)
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
