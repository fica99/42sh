/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/24 23:30:17 by aashara-         ###   ########.fr       */
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
	buf = reading(&g_line);
	set_attr(&g_orig_mode);
	return (buf);
}

char	*reading(t_line *line)
{
	char	c[LINE_MAX + 1];
	short	len;

	len = line->cord->x_cur - line->cord->x_start + ((line->cord->y_cur -
	line->cord->y_start) * line->cord->ws_col);
	get_win_size(g_line.cord);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
	set_end_cord(line->cord);
	check_autocom(line, len);
	g_line_flags = INIT_FLAGS;
	while (READING)
	{
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
