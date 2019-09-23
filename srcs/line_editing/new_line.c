/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:00:27 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 21:01:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

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
