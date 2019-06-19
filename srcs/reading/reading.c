/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/19 19:48:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	read_prompt(t_term *term)
{
	t_cord	*cord;
	t_buff	*buffer;

	cord = term->cord;
	set_start_cord(cord);
	term->history->history_index = double_arr_len(term->history->history_buff);
	buffer = term->buffer;
	if (!(buffer->buffer = ft_strnew(NORMAL_LINE)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
	set_input_mode(&(term->savetty));
	buffer->history_search = NULL;
	reading(buffer, cord, term->history);
	ft_memdel((void**)&(buffer->history_search));
	go_right(ft_strlen(buffer->buffer) - (cord->x_cur - cord->x_start +
			((cord->y_cur - cord->y_start) * cord->ws_col)), cord);
	reset_input_mode(&(g_term.savetty));
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(t_buff *buffer, t_cord *cord, t_history *history)
{
	char	c[LINE_MAX + 1];

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == '\n' && !check_quotes(buffer->buffer, cord))
			break ;
		if (*c == '\n')
			continue;
		if ((*c == CTRL_C && !(g_flags & TERM_HIGHLIGHT)))
		{
			g_flags |= TERM_SIGINT;
			break ;
		}
		while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
				(unsigned)buffer->malloc_len)
			buffer->buffer = strnew_realloc_buf(buffer->buffer,
					buffer->malloc_len += NORMAL_LINE);
		if (!print_symbols(c, buffer, cord, history))
			if (!print_move(c, buffer, cord))
				print_read(c, buffer->buffer, cord);
		if ((g_flags & TERM_SIGINT) || (g_flags & TERM_EXIT))
			break ;
	}
}

void	read_handler(char *c, int fd)
{
	short	nb;

	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode(&(g_term.savetty));
		print_error("42sh", "read() error", NULL, 0);
	}
	c[nb] = '\0';
}

char	*check_quotes(char	*str, t_cord *cord)
{
	short	i;
	short	dquotes;
	short	quotes;
	short	brackets;

	i = -1;
	quotes = 0;
	dquotes = 0;
	brackets = 0;
	while (str[++i])
	{
		if (str[i] == 39)
			quotes++;
		else if (str[i] == 34)
			dquotes++;
		else if (str[i] == '(')
			brackets++;
		else if (str[i] == ')')
			brackets--;
	}
	if (((quotes % 2) != 0 || (dquotes % 2) != 0 || brackets != 0)
	&& !quotes_dquotes_brackets(quotes, dquotes, brackets, cord))
		return (SOMETHING);
	return (NULL);
}

char	*quotes_dquotes_brackets(short quotes, short dquotes, short brackets, t_cord *cord)
{
	short	x;
	short	y;

	x = cord->x_cur;
	y = cord->y_cur;
	if ((quotes % 2) != 0)
		ft_putstr_cord("\nThe number of quotes is incorrect", cord);
	else if ((dquotes % 2) != 0)
		ft_putstr_cord("\nThe number of double quotes is incorrect", cord);
	else if (brackets != 0)
		ft_putstr_cord("\nThe number of brackets is incorrect", cord);
	if (y >= cord->ws_row - 1)
			y--;
	go_to_cord(x, y, STDIN_FILENO);
	get_cur_cord(cord);
	return (NULL);
}
