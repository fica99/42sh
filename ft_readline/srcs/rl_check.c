/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:01:05 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 21:28:58 by aashara-         ###   ########.fr       */
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

void	rl_is_end_window(t_rl_cord *cord)
{
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
}

char	rl_check_empty_line(char *line)
{
	short	i;

	if (!line)
		return (FALSE);
	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (TRUE);
	return (FALSE);
}

void	rl_check_str_mem(t_buff *buffer, char *c)
{
	char	*copy;

	buffer->max_len += ft_strlen(c);
	while (buffer->max_len >= buffer->malloc_len)
	{
		if (!(copy = ft_strdup(buffer->buffer)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_strdel(&buffer->buffer);
		buffer->malloc_len += MAX_LINE_SIZE;
		if (!(buffer->buffer = ft_strnew(buffer->malloc_len)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_strcpy(buffer->buffer, copy);
		ft_strdel(&copy);
	}
}
