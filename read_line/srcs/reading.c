/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/22 17:33:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_readline(char *prompt)
{
	char	*buf;

	g_line_flags = INIT_FLAGS;
	if (prompt)
		write_prompt(prompt);
	else
		standart_prompt();
	buf = reading(&g_line);
	while (g_line_flags & AUTOCOM)
		buf = ft_readline(prompt);
	return (buf);
}

char	*reading(t_line *line)
{
	char	c[LINE_MAX + 1];
	short	pos;

	set_input_mode(&g_raw_mode);
	pos = line->cord->pos;
	unset_cord(line->cord);
	get_win_size(line->cord);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
	set_end_cord(line->cord);
	ft_putstr_cord(line->buffer.buffer, line->cord);
	go_left(ft_strlen(line->buffer.buffer) - pos, line->cord);
	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		check_malloc_len_buffer(&(line->buffer), c);
		find_templ(c, line);
		if (g_line_flags & BREAK_FLAG)
			break ;
	}
	set_attr(&g_orig_mode);
	return (line->buffer.buffer);
}

void		read_handler(char *c, int fd)
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
