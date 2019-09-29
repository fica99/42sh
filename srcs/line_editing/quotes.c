/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:35:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/29 22:00:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	check_quotes(t_line *line)
{
	short	i;
	short	dq;
	short	q;
	short	br;
	char	*buf;

	i = -1;
	q = 0;
	dq = 0;
	br = 0;
	buf = line->buffer.buffer;
	while (buf[++i])
	{
		if (buf[i] == '\'')
			q++;
		else if (buf[i] == '"')
			dq++;
		else if (buf[i] == '(')
			br++;
		else if (buf[i] == ')')
			br--;
	}
	if (!quotes_dquotes_brackets(q, dq, br, line))
		g_line_flags |= BREAK_FLAG;
}

char	quotes_dquotes_brackets(short q, short dq, short br, t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	if (dq % 2 != 0)
		print_quotes(0, dq, 0, line);
	else if (q % 2 != 0)
		print_quotes(q, 0, 0, line);
	else if (br != 0)
		print_quotes(0, 0, br, line);
	else if (line->buffer.buffer[cord->pos - 1] == '\\')
	{
		print_quotes(0, 0, 0, line);
		line->buffer.buffer = ft_strdel_el(line->buffer.buffer, --cord->pos);
		line->buffer.buffer = ft_strdel_el(line->buffer.buffer, --cord->pos);
	}
	else
		return (FALSE);
	return (TRUE);
}

void	print_quotes(short q, short dq, short br, t_line *line)
{
	char	*ps2;

	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	line->buffer.buffer = ft_stradd(line->buffer.buffer, "\n",
	line->cord->pos);
	if ((dq % 2) != 0)
		ft_putstr_fd(DQUOTES_ERROR, STDIN_FILENO);
	else if ((q % 2) != 0)
		ft_putstr_fd(QUOTES_ERROR, STDIN_FILENO);
	else if (br != 0)
		ft_putstr_fd(BRACKETS_ERROR, STDIN_FILENO);
	else if (!(ps2 = ft_getenv("PS2")))
		ft_putstr_fd("> ", STDIN_FILENO);
	else
		write_prompt(ps2);
	++(line->cord->pos);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
	set_end_cord(line->cord);
	line->history_index = g_history.hist_len;
}
