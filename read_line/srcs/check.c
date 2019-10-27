/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:30:00 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	is_start_pos(t_cord *cord)
{
	if ((cord->x_cur <= cord->x_start) && (cord->y_cur <= cord->y_start))
		return (TRUE);
	return (FALSE);
}

char	is_end_pos(t_cord *cord)
{
	if ((cord->x_cur >= cord->x_end) && (cord->y_cur >= cord->y_end))
		return (TRUE);
	return (FALSE);
}

void	check_malloc_len_buffer(t_buff *buffer, char *c)
{
	while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
			(unsigned)buffer->malloc_len)
		buffer->buffer = ft_strdup_realloc(buffer->buffer,
		buffer->malloc_len += NORMAL_LINE);
}

void	check_end_window(t_cord *cord)
{
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
}

void	check_quotes(char *c)
{
	int		i;
	int		q;
	int		dq;
	char	*prompt;

	i = -1;
	q = 0;
	dq = 0;
	while (c[++i])
	{
		if (c[i] == '\'')
			++q;
		if (c[i] == '\"')
			++dq;
	}
	g_line.buffer.buffer = ft_stradd(g_line.buffer.buffer, "\n",
	g_line.cord->pos++);
	if ((q % 2) || (dq % 2))
		ft_readline(!(prompt = ft_getenv("PS2")) ? "> " : prompt);
}
