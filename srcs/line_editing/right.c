/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:31:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 18:12:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		key_right(t_line *line)
{
	if (((short)ft_strlen(line->buffer.buffer) > line->cord->pos))
	{
		go_right(1, line->cord);
		return (1);
	}
	return (0);
}

char		key_home(t_line *line)
{
	if (((short)ft_strlen(line->buffer.buffer) > line->cord->pos))
	{
		go_right(ft_strlen(line->buffer.buffer + line->cord->pos), line->cord);
		return (1);
	}
	return (0);
}

char		ctrl_right(t_line *line)
{
	next_word(line->buffer.buffer + line->cord->pos, cord);
	return (1);
}

char		ctrl_down(t_line *line)
{
	short	len;
	t_cord	*cord;

	cord = line->cord;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if ((cord->pos + cord->ws_col <= (short)ft_strlen(line->buffer.buffer))
	&& !(g_line_flags & TERM_NL))
	{
		go_right(cord->ws_col, cord);
		return (1);
	}
	return (0);
}

void		go_right(short i, t_cord *cord)
{
	if (i <= 0)
		return ;
	cord->pos += i;
	check_nl_right(cord, i);
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	check_nl_right(t_cord *cord, short i)
{
	t_cord	*new_line;

	cord->x_cur += i;
	new_line = cord->nl;
	while (new_line)
	{
		if ((cord->y_start + new_line->y_cur) == cord->y_cur && cord->x_cur >
		new_line->x_cur)
		{
			i = cord->x_cur - new_line->x_cur - 1;
			cord->x_cur = 0;
			cord->y_cur++;
			check_nl_right(cord, i);
		}
		new_line = new_line->nl;
	}
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
}

void		next_word(char *buf, t_cord *cord)
{
	short	i;
	char	flag;

	i = 0;
	flag = 0;
	while (buf[i])
	{
		if (buf[i] == ' ' || buf[i] == '\n')
			flag = 1;
		if ((ft_isalpha(buf[i]) || ft_isdigit(buf[i])) && flag)
			break ;
		i++;
	}
	go_right(i, cord);
}
