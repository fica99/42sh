/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:29:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 18:09:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	key_left(t_line *line)
{
	if (!is_start_pos(line->cord))
	{
		go_left(1, line->cord);
		return (1);
	}
	return (0);
}

char	key_home(t_line *line)
{
	if (!is_start_pos(line->cord))
	{
		go_left(cord->pos, line->cord);
		return (1);
	}
	return (0);
}

char		ctrl_left(t_line *line)
{
	prev_word(line->buffer.buffer, line->cord);
	return (1);
}

char		ctrl_up(t_line *line)
{
	short	len;
	t_cord	*cord;

	cord = line->cord;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if (len - cord->ws_col >= 0 && !(g_line_flags & TERM_NL))
	{
		go_left(cord->ws_col, cord);
		return (1);
	}
	return (0);
}

void		go_left(short i, t_cord *cord)
{
	short	len;

	if (i <= 0)
		return ;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
			* cord->ws_col);
	if (i > len)
		i = len;
	cord->pos -= i;
	check_nl_left(cord, i);
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	check_nl_left(t_cord *cord, short i)
{
	t_cord	*new_line;

	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
		new_line = cord->nl;
		while (new_line)
		{
			if ((cord->y_start + new_line->y_cur) == cord->y_cur)
			{
				cord->x_cur -= cord->ws_col - new_line->x_cur - 1;
				break ;
			}
			new_line = new_line->nl;
		}
	}
}

void		prev_word(char *buf, t_cord *cord)
{
	short	i;

	i = cord->pos;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ' || buf[i - 1] == '\n') &&
		(ft_isalpha(buf[i]) || ft_isdigit(buf[i])))
		{
			go_left(cord->pos - i, cord);
			break ;
		}
	}
}
