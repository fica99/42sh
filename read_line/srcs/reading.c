/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/28 14:31:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_readline(char *prompt)
{
	char	*buf;

	if (prompt && *prompt)
		ft_strcpy(g_prompt, prompt);
	write_prompt(g_prompt);
	set_input_mode(&g_raw_mode);
	get_win_size(g_line.cord);
	get_cur_cord(g_line.cord);
	set_start_cord(g_line.cord);
	set_end_cord(g_line.cord);
	buf = reading(&g_line);
	set_attr(&g_orig_mode);
	return (buf);
}

char	*reading(t_line *line)
{
	char	c[LINE_MAX + 1];

	ft_putstr_cord(line->buffer.buffer + line->cord->pos, line->cord);
	g_line_flags = INIT_FLAGS;
	while (READING)
	{
		signal(SIGWINCH, win_handler);
		read_handler(c, STDIN_FILENO);
		check_malloc_len_buffer(&(line->buffer), c);
		find_templ(c, line);
		if (g_line_flags & BREAK_FLAG)
			break ;
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
