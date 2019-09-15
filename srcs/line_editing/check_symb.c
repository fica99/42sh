/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/09/15 16:02:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*print_move(char *c, char *buffer, t_cord *cord)
{
	short	len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	if ((!ft_strcmp(c, K_LFT) || !ft_strcmp(c, K_HOME)) &&
	!is_start_pos(cord))
		!ft_strcmp(c, K_LFT) ? go_left(1, cord) : go_left(cord->pos, cord);
	else if ((!ft_strcmp(c, K_RGHT) || !ft_strcmp(c, K_END))
	&& ((short)ft_strlen(buffer) > cord->pos))
		!ft_strcmp(c, K_RGHT) ? go_right(1, cord) :
		go_right(ft_strlen(buffer + cord->pos), cord);
	else if (!ft_strcmp(c, CTRL_LEFT) || !ft_strcmp(c, CTRL_RIGHT))
		!ft_strcmp(c, CTRL_RIGHT) ? next_word(buffer + cord->pos, cord) :
		prev_word(buffer, cord);
	else if (!(ft_strcmp(c, CTRL_UP)) && len - cord->ws_col >= 0 &&
	!(g_line_flags & TERM_NL))
		go_left(cord->ws_col, cord);
	else if (!ft_strcmp(c, CTRL_DOWN) && (cord->pos + cord->ws_col <=
	(short)ft_strlen(buffer)) && !(g_line_flags & TERM_NL))
		go_right(cord->ws_col, cord);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_symbols(char *c, t_line *line)
{
	if (!ft_strcmp(c, SHIFT_LFT) || !ft_strcmp(c, SHIFT_RGHT) ||
		*c == CTRL_V || *c == CTRL_C || *c == CTRL_X)
		cut_copy_paste(c, line);
	else
		disable_highlight(line->cord, line->buffer.buffer);
	if (*c == TAB && !(g_line_flags & HISTORY_SEARCH) &&
	!(g_line_flags & TERM_QUOTES) && !(g_line_flags & TERM_HIGHLIGHT))
		autocomplite(&line->buffer, line->cord);
	else if (!ft_strcmp(c, K_UP) || !ft_strcmp(c, K_DOWN)
	|| *c == CTRL_R || (g_line_flags & HISTORY_SEARCH))
		go_history(c, line);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_printable(char *c, char *buffer, t_cord *cord)
{
	if (((*c == BCSP || *c == CTRL_H) && !is_start_pos(cord)) ||
	!ft_strcmp(c, K_DEL) || *c == CTRL_D)
	{
		autocomplite(NULL, NULL);
		if (*c == BCSP || *c == CTRL_H)
			go_left(1, cord);
		if ((!ft_strlen(buffer) || (g_line_flags & HEREDOC_FLAG))
		&& *c == CTRL_D)
		{
			g_line_flags |= BREAK_FLAG;
			if (!ft_strlen(buffer))
				g_flags |= TERM_EXIT;
			return (SOMETHING);
		}
		del_symb(buffer, cord);
	}
	else if (ft_isprint(*c) || *c == NEW_LINE)
	{
		autocomplite(NULL, NULL);
		print_symb(c, buffer, cord);
	}
	else
		return (NULL);
	return (SOMETHING);
}

void	check_new_line(t_line *line, char *c)
{
	if (*c == NEW_LINE)
	{
		if (!(g_line_flags & HEREDOC_FLAG))
		{
			if (!(g_line_flags & TERM_QUOTES))
			{
				if (!check_heredoc(line->buffer, &line->stop_buff, line->cord))
					check_quotes(line);
			}
			else
				check_quotes(line);
		}
		else
			check_heredoc_end(line->buffer.buffer, line->stop_buff.buffer,
			line->cord);
	}
	if (*c == CTRL_D && (g_line_flags & HEREDOC_FLAG))
	{
		line->buffer.buffer = ft_stradd(line->buffer.buffer, "\n",
		ft_strlen(line->buffer.buffer));
		g_line_flags |= HEREDOC_CTRL_D;
		g_line_flags |= BREAK_FLAG;
	}
}
