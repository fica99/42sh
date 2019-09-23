/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/23 23:12:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*read_prompt(void)
{
	char	*buff;

	buff = NULL;
	set_input_mode(&g_raw_mode);
	transmit_mode();
	set_data(&g_line);
	reading(&g_line);
	autocomplite(NULL, NULL);
	if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT) &&
	*(g_line.buffer.buffer))
	{
		//write_hered(&g_line.buffer.buffer);
		if (!(buff = ft_strdup(g_line.buffer.buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
		write_history(buff, &g_history);
	}
	unset_data(&g_line);
	reset_transmit_mode();
	set_attr(&g_orig_mode);
	return (buff);
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
		find_templ(c, line);
		if ((g_flags & TERM_EXIT) || (g_line_flags & BREAK_FLAG))
			break ;
	}
	go_right(ft_strlen(line->buffer.buffer + line->cord->pos),
	line->cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
}

void		read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		go_right(ft_strlen(g_line.buffer.buffer) - g_line.cord->pos,
		g_line.cord);
		ft_putchar_fd(NEW_LINE, STDERR_FILENO);
		err_exit(g_argv[0], "read() error", NULL, NOERROR);
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
