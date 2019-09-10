/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:35:01 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/02 17:45:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	check_quotes(t_line *line)
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
		if (line->buffer.buffer[i] == '\'')
			q++;
		else if (line->buffer.buffer[i] == '"')
			dq++;
		else if (line->buffer.buffer[i] == '(')
			br++;
		else if (line->buffer.buffer[i] == ')')
			br--;
	}
	if (i != 0)
		if (quotes_dquotes_brackets(q, dq, br, line))
			return ;
	g_line_flags |= BREAK_FLAG;
}

char	*quotes_dquotes_brackets(short q, short dq, short br, t_line *line)
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
		return (NULL);
	g_line_flags |= TERM_QUOTES;
	return (SOMETHING);
}

void	print_quotes(short q, short dq, short br, t_line *line)
{
	go_right(ft_strlen(line->buffer.buffer) - line->cord->pos, line->cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	line->history.history_index = ft_darlen(line->history.history_buff);
	if ((q % 2) != 0)
		ft_putstr_fd("\nquotes> ", STDIN_FILENO);
	else if ((dq % 2) != 0)
		ft_putstr_fd("\ndquotes> ", STDIN_FILENO);
	else if (br != 0)
		ft_putstr_fd("\nbrackets> ", STDIN_FILENO);
	else
	{
		ft_putchar_fd(NEW_LINE, STDIN_FILENO);
		if (!ft_getenv("PS2"))
			ft_putstr_fd("> ", STDIN_FILENO);
		else
			write_prompt(ft_getenv("PS2"),
			ft_darlen(line->history.history_buff), g_argv[0]);
	}
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
}
