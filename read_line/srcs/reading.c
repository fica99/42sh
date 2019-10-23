/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 20:43:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_readline(char *prompt)
{
	char	*buf;
	short	pos;

	g_line_flags = INIT_FLAGS;
	if (prompt)
		write_prompt(prompt);
	else
		standart_prompt();
	set_input_mode(&g_raw_mode);
	pos = g_line.cord->pos;
	unset_cord(g_line.cord);
	set_start_params();
	ft_putstr_cord(g_line.buffer.buffer, g_line.cord);
	go_left(ft_strlen(g_line.buffer.buffer) - pos, g_line.cord);
	buf = reading(&g_line);
	if (g_line_flags & AUTOCOM)
		buf = ft_readline(prompt);
	set_attr(&g_orig_mode);
	return (buf);
}

char	*reading(t_line *line)
{
	char	c[LINE_MAX + 1];
	char	*ps2;

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		check_malloc_len_buffer(&(line->buffer), c);
		check_quotes(line->buffer.buffer);
		find_templ(c, line);
		if (g_line_flags & BREAK_FLAG)
			break ;
	}
	if (g_line_flags & QUOTES)
	{
		g_line_flags &= ~ BREAK_FLAG;
		if (!(ps2 = ft_getenv("PS2")))
			ps2 = "> ";
		write_prompt(ps2);
		set_start_params();
		reading(&g_line);
	}
	return (line->buffer.buffer);
}

void	read_handler(char *c, int fd)
{
	short	nb;

	ft_putstr_fd(TRANSMIT_MODE, STDIN_FILENO);
	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
		err_exit(g_argv[0], "read() error", NULL, NOERROR);
	}
	c[nb] = '\0';
	ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
}
