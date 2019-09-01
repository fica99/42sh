/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/09/01 17:36:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*print_move(char *c, char *buffer, t_cord *cord)
{
	short	len;

	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
	cord->ws_col);
	disable_highlight(cord, buffer);
	if ((!ft_strcmp(c, tigetstr("kcub1")) || !ft_strcmp(c, tigetstr("khome")))
	&& !is_start_pos(cord))
		!ft_strcmp(c, tigetstr("kcub1")) ? go_left(1, cord) : go_left(cord->pos,
		cord);
	else if ((!ft_strcmp(c, tigetstr("kcuf1")) || !ft_strcmp(c,
	tigetstr("kend"))) && ((short)ft_strlen(buffer) > cord->pos))
		!ft_strcmp(c, tigetstr("kcuf1")) ? go_right(1, cord) :
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
	if (!ft_strcmp(c, tigetstr("kLFT")) || !ft_strcmp(c, tigetstr("kRIT")) ||
		*c == CTRL_V || *c == CTRL_C || *c == CTRL_X)
		cut_copy_paste(c, line);
	else if (*c == TAB && !(g_line_flags & HISTORY_SEARCH) &&
	!(g_line_flags & TERM_QUOTES) && !(g_line_flags & TERM_HIGHLIGHT))
		autocomplite(&line->buffer, line->cord);
	else if (!ft_strcmp(c, tigetstr("kcuu1")) ||
	!ft_strcmp(c, tigetstr("kcud1"))
	|| *c == CTRL_R || (g_line_flags & HISTORY_SEARCH))
		go_history(c, line);
	else
		return (NULL);
	return (SOMETHING);
}

char	*print_printable(char *c, char *buffer, t_cord *cord)
{
	if (((*c == BCSP || *c == CTRL_H) && !is_start_pos(cord)) ||
	!ft_strcmp(c, tigetstr("kdch1")) || *c == CTRL_D)
	{
		autocomplite(NULL, NULL);
		if (*c == BCSP || *c == CTRL_H)
			go_left(1, cord);
		if (!ft_strlen(buffer) && *c == CTRL_D)
		{
			g_flags |= TERM_EXIT;
			return (SOMETHING);
		}
		del_symb(buffer, cord);
	}
	else if (ft_isprint(*c) || *c == '\n')
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
}
