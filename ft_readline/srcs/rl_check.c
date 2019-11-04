/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:01:05 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/04 18:16:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	rl_is_start_pos(t_rl_cord cord)
{
	if ((cord.x_cur <= cord.x_start) && (cord.y_cur <= cord.y_start))
		return (TRUE);
	return (FALSE);
}

char	rl_is_end_pos(t_rl_cord cord)
{
	if ((cord.x_cur >= cord.x_end) && (cord.y_cur >= cord.y_end))
		return (TRUE);
	return (FALSE);
}

void	rl_malloc_len(t_rl_buff *buffer, char *c)
{
	while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
			(unsigned)buffer->malloc_len)
		buffer->buffer = ft_strdup_realloc(buffer->buffer,
		buffer->malloc_len += MAX_LINE_SIZE);
}

void	rl_is_end_window(t_rl_cord *cord)
{
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
}

void	rl_check_quotes(char *c, t_readline *rl)
{
	int		i;
	int		q;
	int		dq;
	char	*ps2;

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
	if (!(q % 2) && !(dq % 2) && c[i - 1] != '\\')
		return ;
	if (c[i - 1] == '\\')
		rl->line.buffer = ft_strdel_el(rl->line.buffer,
		--rl->cord.pos);
	else
		rl->line.buffer = ft_stradd(rl->line.buffer, "\n",
		rl->cord.pos++);
	ft_strcpy(rl->prompt, (!(ps2 = ft_getenv("PS2", rl->env)) ? "> " : ps2));
	rl_reading(rl);
}
