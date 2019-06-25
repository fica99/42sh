/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:39:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/25 21:25:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*check_quotes(char	*str, t_cord *cord)
{
	short	i;
	short	dquotes;
	short	quotes;
	short	brackets;

	if (!str)
		return (NULL);
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
	go_right(ft_strlen(g_term.buffer->buffer) - cord->pos,cord);
	g_flags |= TERM_QUOTES;
	g_term.history->history_index = double_arr_len(g_term.history->history_buff);
	if ((quotes % 2) != 0)
		ft_putstr_fd("\nquotes> ", STDIN_FILENO);
	else if ((dquotes % 2) != 0)
		ft_putstr_fd("\ndquotes> ", STDIN_FILENO);
	else if (brackets != 0)
		ft_putstr_fd("\nbrackets> ", STDIN_FILENO);
	get_cur_cord(cord);
	set_start_cord(cord);
	return (NULL);
}
