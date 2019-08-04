/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:39:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/04 14:08:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*check_quotes(t_line *line)
{
	short	i;
	short	dq;
	short	q;
	short	br;

	i = -1;
	q = 0;
	dq = 0;
	br = 0;
	while (line->buffer.buffer[++i])
	{
		if (line->buffer.buffer[i] == 39)
			q++;
		else if (line->buffer.buffer[i] == 34)
			dq++;
		else if (line->buffer.buffer[i] == '(')
			br++;
		else if (line->buffer.buffer[i] == ')')
			br--;
	}
	if (((q % 2) != 0 || (dq % 2) != 0 || br != 0 || (i != 0 && line->buffer.
	buffer[i - 1] == '\\')) && !quotes_dquotes_brackets(q, dq, br, line))
		return (SOMETHING);
	return (NULL);
}

char	*quotes_dquotes_brackets(short q, short dq, short br, t_line *line)
{
	go_right(ft_strlen(line->buffer.buffer) - line->cord->pos, line->cord);
	g_flags |= TERM_QUOTES;
	line->history.history_index = ft_darlen(line->history.history_buff);
	if ((q % 2) != 0)
		ft_putstr_fd("\nquotes> ", STDIN_FILENO);
	else if ((dq % 2) != 0)
		ft_putstr_fd("\ndquotes> ", STDIN_FILENO);
	else if (br != 0)
		ft_putstr_fd("\nbrackets> ", STDIN_FILENO);
	else
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		if (!ft_getenv("PS2"))
			ft_putstr_fd("> ", STDIN_FILENO);
		else
			write_prompt(ft_getenv("PS2"),
			ft_darlen(line->history.history_buff), g_argv[0]);
	}
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
	return (NULL);
}
