/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:35:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 21:13:13 by aashara-         ###   ########.fr       */
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
	if (i != 0)
		if (!quotes_dquotes_brackets(q, dq, br, line))
			g_line_flags |= BREAK_FLAG;
}

char	quotes_dquotes_brackets(short q, short dq, short br, t_line *line)
{
	if (q % 2 != 0)
		print_quotes(q, 0, 0, line);
	else if (dq % 2 != 0)
		print_quotes(0, dq, 0, line);
	else if (br != 0)
		print_quotes(0, 0, br, line);
	else if (line->buffer.buffer[ft_strlen(line->buffer.buffer) - 1] == '\\')
		print_quotes(0, 0, 0, line);
	else
		return (FALSE);
	return (TRUE);
}

void	print_quotes(short q, short dq, short br, t_line *line)
{
	t_cord	*cord;
	short	pos;

	cord = line->cord;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	pos = cord->pos;
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	if (cord->y_cur >= cord->ws_row - 1)
		(cord->y_start)--;
	else
		(cord->y_cur)++;
	cord->x_cur = 0;
	if ((q % 2) != 0)
		ft_putstr_cord(QUOTES_ERROR, cord);
	else if ((dq % 2) != 0)
		ft_putstr_cord(DQUOTES_ERROR, cord);
	else if (br != 0)
		ft_putstr_cord(BRACKETS_ERROR, cord);
	go_to_cord(cord->x_start, cord->y_start, STDIN_FILENO);
	cord->pos = 0;
	cord->x_cur = cord->x_start;
	cord->y_cur = cord->y_start;
	go_right(pos, cord);
	set_end_cord(cord);
}
