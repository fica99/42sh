/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:00 by filip             #+#    #+#             */
/*   Updated: 2019/09/18 21:12:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	check_symbol(char *c, t_line *line)
{
	if (!ft_strcmp(c, K_UP))
		history_up(line);
	else if (!ft_strcmp(c, K_DOWN))
		history_down(line);
	else if (!ft_strcmp(c, KEY_LEFT))
		key_left(line);
	else if (!ft_strcmp(c, KEY_LEFT))
		key_right(line);

}

void	key_right(t_line *line)
{

}

void	key_left(t_line *line)
{
	if (!is_start_pos(line->cord))
		go_left(1, line);
}

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = SET_CUR;
	ft_putstr_fd(tparm(cursor, y, x), fd);
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

void		go_right(short i, t_cord *cord)
{
	if (i <= 0)
		return ;
	cord->pos += i;
	check_nl_right(cord, i);
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
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

void		copy_highlight(t_buff *copy_buff, t_buff *buffer, t_cord *cord)
{
	ft_memdel((void**)&(copy_buff->buffer));
	copy_buff->malloc_len = buffer->malloc_len;
	if (!(copy_buff->buffer = ft_strnew(copy_buff->malloc_len)))
	{
		go_right(ft_strlen(g_line.buffer.buffer) - g_line.cord->pos,
		g_line.cord);
		ft_putchar_fd('\n', STDERR_FILENO);
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	if ((cord->pos - cord->highlight_pos) >= 0)
		copy_buff->buffer = copy_from_buff(buffer->buffer, copy_buff->buffer,
		cord->highlight_pos, cord->pos);
	else
		copy_buff->buffer = copy_from_buff(buffer->buffer, copy_buff->buffer,
		cord->pos, cord->highlight_pos);
}

void		paste_highlight(t_buff *buffer, t_buff *copy_buff, t_cord *cord)
{
	short	position;

	check_malloc_len_buffer(buffer, copy_buff->buffer);
	buffer->buffer = ft_stradd(buffer->buffer, copy_buff->buffer, cord->pos);
	position = cord->pos;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buffer->buffer + cord->pos, cord);
	go_left(cord->pos - position, cord);
	disable_highlight(cord, buffer->buffer);
}

void		cut_highlight(t_buff *buffer, t_cord *cord)
{
	short	pos;
	short	j;

	pos = cord->pos;
	if ((cord->pos - cord->highlight_pos) >= 0)
	{
		j = cord->highlight_pos;
		while (j++ <= cord->pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->highlight_pos);
	}
	else
	{
		j = cord->pos;
		while (j++ <= cord->highlight_pos)
			buffer->buffer = ft_strdel_el(buffer->buffer, cord->pos);
	}
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buffer->buffer + cord->pos, cord);
	((pos - cord->highlight_pos) < 0) ? go_left(ft_strlen(buffer->buffer) - pos,
	cord) : go_left(ft_strlen(buffer->buffer) - cord->highlight_pos, cord);
	disable_highlight(cord, buffer->buffer);
}





short		is_start_pos(t_cord *cord)
{
	if ((cord->x_cur == cord->x_start) && (cord->y_cur == cord->y_start))
		return (1);
	return (0);
}

void		check_end_window(t_cord *cord)
{
	if (cord->y_cur >= cord->ws_row - 1)
		(cord->y_start)--;
	else
		(cord->y_cur)++;
}

void	unset_start_pos(t_cord *cord)
{
	cord->x_start = 0;
	cord->y_start = 0;
}

void		disable_highlight(t_cord *cord, char *buffer)
{
	short	pos;

	if (g_line_flags & TERM_HIGHLIGHT)
	{
		g_line_flags &= ~TERM_HIGHLIGHT;
		pos = cord->pos;
		go_left(cord->pos, cord);
		ft_putstr_cord(buffer + cord->pos, cord);
		go_left(cord->pos - pos, cord);
	}
	if (g_line_flags & START_POS)
		g_line_flags &= ~START_POS;
	cord->highlight_pos = 0;
}

void		highlight_left(char *buffer, t_cord *cord)
{
	short	position;

	position = cord->pos;
	g_line_flags |= TERM_HIGHLIGHT;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (cord->highlight_pos >= position - 1)
		ft_putstr_highlight(buffer + cord->pos, position - 1 - cord->pos,
		cord->highlight_pos - cord->pos, cord);
	else
		ft_putstr_highlight(buffer + cord->pos, cord->highlight_pos - cord->pos,
		position - 1 - cord->pos, cord);
	go_left(cord->pos - (position - 1), cord);
}

void		highlight_right(char *buffer, t_cord *cord)
{
	short	position;

	position = cord->pos;
	g_line_flags |= TERM_HIGHLIGHT;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (cord->highlight_pos >= position + 1)
		ft_putstr_highlight(buffer + cord->pos, position + 1 - cord->pos,
		cord->highlight_pos - cord->pos, cord);
	else
		ft_putstr_highlight(buffer + cord->pos, cord->highlight_pos - cord->pos,
		position + 1 - cord->pos, cord);
	go_left(cord->pos - (position + 1), cord);
}

void		ft_putstr_highlight(char *str, short start, short end, t_cord *cord)
{
	short	i;
	char	*symb;

	i = -1;
	if (!(symb = ft_strnew(1)))
	{
		go_right(ft_strlen(g_line.buffer.buffer) - cord->pos, cord);
		ft_putchar_fd('\n', STDERR_FILENO);
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	if (start <= i)
		HIGHLIGHT(STDIN_FILENO);
	while (str[++i])
	{
		if (i == start)
			HIGHLIGHT(STDIN_FILENO);
		symb[0] = str[i];
		ft_putstr_cord(symb, cord);
		if (i == end)
			STANDART(STDIN_FILENO);
	}
	ft_memdel((void**)&symb);
	STANDART(STDIN_FILENO);
}

void		go_history(char *c, t_line *line)
{

	if (((*c == CTRL_R && len) || (g_line_flags & HISTORY_SEARCH)) &&
	!(g_line_flags & TERM_QUOTES))
	{
		go_to_cord(line->cord->x_start, line->cord->y_start, STDIN_FILENO);
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		if (!(g_line_flags & HISTORY_SEARCH))
		{
			ft_putstr_fd("(History search)'", STDIN_FILENO);
			g_line_flags |= HISTORY_SEARCH;
		}
		get_cur_cord(line->cord);
		set_start_cord(line->cord);
		line->cord->pos = 0;
		find_history(c, line);
	}

	else if (!ft_strcmp(c, K_DOWN) &&
	line->history.history_index != len)
		history_down(line, len);
}

void		find_history(char *symbol, t_line *line)
{
	check_malloc_len_buffer(&line->history_search, symbol);
	ft_putstr_cord(line->history_search.buffer, line->cord);
	if (!print_printable(symbol, line->history_search.buffer, line->cord) &&
	*symbol != CTRL_R)
	{
		g_line_flags &= ~HISTORY_SEARCH;
		unset_start_pos(line->cord);
		go_left(line->cord->pos + 17, line->cord);
		set_start_cord(line->cord);
		line->cord->pos = 0;
		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
		ft_putstr_cord(line->buffer.buffer, line->cord);
		ft_strclr(line->history_search.buffer);
		if (!print_move(symbol, line->buffer.buffer, line->cord))
			print_symbols(symbol, line);
		return ;
	}
	ft_putstr_fd("': ", STDIN_FILENO);
	get_cur_cord(line->cord);
	line->cord->pos = 0;
	ft_putstr_cord(check_history(&line->history, &line->buffer,
	&line->history_search), line->cord);
}

char		*check_history(t_history *history, t_buff *buffer,
t_buff *history_search)
{
	short	i;

	i = -1;
	while (history->history_buff[++i])
	{
		if (ft_strstr(history->history_buff[i], history_search->buffer) &&
		*(history_search->buffer) != '\0')
		{
			check_malloc_len_buffer(buffer, history->history_buff[i]);
			ft_strclr(buffer->buffer);
			ft_strcat(buffer->buffer, history->history_buff[i]);
			break ;
		}
	}
	return (buffer->buffer);
}


void	set_start_cord(t_cord *cord)
{
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
}


char		*cut_copy_paste(char *c, t_line *line)
{
	if (!line->cord->highlight_pos && !(g_line_flags & START_POS))
		line->cord->highlight_pos = line->cord->pos;
	if (!line->cord->highlight_pos)
		g_line_flags |= START_POS;
	if (!ft_strcmp(c, SHIFT_LFT) && !is_start_pos(line->cord))
		highlight_left(line->buffer.buffer, line->cord);
	else if (!ft_strcmp(c, SHIFT_RGHT) &&
	((short)ft_strlen(line->buffer.buffer) > line->cord->pos))
		highlight_right(line->buffer.buffer, line->cord);
	else if (*c == CTRL_C && (g_line_flags & TERM_HIGHLIGHT))
		copy_highlight(&line->copy_buff, &line->buffer, line->cord);
	else if (*c == CTRL_V && line->copy_buff.buffer)
		paste_highlight(&line->buffer, &line->copy_buff, line->cord);
	else if (*c == CTRL_X)
	{
		copy_highlight(&line->copy_buff, &line->buffer, line->cord);
		cut_highlight(&line->buffer, line->cord);
	}
	else
		return (NULL);
	return (SOMETHING);
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

void		history_up(t_line *line)
{
	short	len;

	len = ft_darlen(line->history.history_buff);
	if (!(len) || !line->history.history_index)
		return ;
	go_left(line->cord->pos, line->cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (--(line->history.history_index) == len - 1)
	{
		check_malloc_len_buffer(&line->save_buff,
		line->buffer.buffer + line->cord->pos);
		ft_strcat(line->save_buff.buffer, line->buffer.buffer +
		line->cord->pos);
	}
	ft_strclr(line->buffer.buffer + line->cord->pos);
	check_malloc_len_buffer(&line->buffer,
	line->history.history_buff[line->history.history_index]);
	ft_strcat(line->buffer.buffer, line->history.history_buff[(line->
	history.history_index)]);
	ft_putstr_cord(line->buffer.buffer + line->cord->pos, line->cord);
}

void		history_down(t_line *line)
{
	char	*history_buffer;
	short	len;

	len = ft_darlen(line->history.history_buff);
	if (!len || line->history.history_index == len)
		return ;
	go_left(line->cord->pos, line->cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (++(line->history.history_index) == len)
		history_buffer = line->save_buff.buffer;
	else
		history_buffer = line->history.history_buff[(line->
		history.history_index)];
	ft_strclr(line->buffer.buffer + line->cord->pos);
	check_malloc_len_buffer(&line->buffer, history_buffer);
	ft_strcat(line->buffer.buffer, history_buffer);
	ft_putstr_cord(line->buffer.buffer + line->cord->pos, line->cord);
	if (line->history.history_index == len)
		ft_strclr(line->save_buff.buffer);
}












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



void		del_symb(char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_strdel_el(buf, cord->pos);
	pos = cord->pos;
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos, cord);
}

void		print_symb(char *c, char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_stradd(buf, c, cord->pos);
	pos = cord->pos;
	if (*c == NEW_LINE)
		cord->pos++;
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos - ft_strlen(c), cord);
	if (*c == NEW_LINE && buf[cord->pos - 2] == '\\')
	{
		buf = ft_strdel_el(buf, --cord->pos);
		buf = ft_strdel_el(buf, --cord->pos);
	}
}

void		ft_putstr_cord(char *str, t_cord *cord)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (*str == NEW_LINE)
			save_cord(cord);
		else
			(cord->x_cur)++;
		if (cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd(NEW_LINE, STDIN_FILENO);
			cord->x_cur = 0;
			check_end_window(cord);
		}
		str++;
		cord->pos++;
	}
}

void		save_cord(t_cord *cord)
{
	t_cord	*new_line;
	t_cord	*copy;

	g_line_flags |= TERM_NL;
	new_line = cord;
	while (new_line->nl)
	{
		if (new_line->nl->y_cur == (cord->y_cur - cord->y_start))
		{
			copy = new_line->nl;
			new_line->nl = copy->nl;
			ft_memdel((void**)&(copy));
			continue ;
		}
		new_line = new_line->nl;
	}
	new_line->nl = init_cord();
	new_line->nl->x_cur = cord->x_cur;
	new_line->nl->y_cur = cord->y_cur - cord->y_start;
	cord->x_cur = 0;
	check_end_window(cord);
}

void	find_templ(char *str, t_line *line)
{
	t_temp	*temp;

	temp = line->temp;
	while (temp)
	{
		if (match_str_templ(str, temp->template))
			if ((temp->handler()))
				break ;
		temp = temp->next;
	}
}

int		match_str_templ(char *str, char *templ)
{
	if (str && templ)
	{
		if (!(*str) && !(*templ))
			return (1);
		if (*str == *templ)
			return (check_str_teml(str + 1, templ + 1));
	}
	return (0);
}


