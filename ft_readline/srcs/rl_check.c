/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:48:50 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 15:01:56 by aashara-         ###   ########.fr       */
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

void	rl_check_str_mem(t_buff *buffer, char *c)
{
	char	*copy;

	buffer->cur_len += ft_strlen(c);
	while (buffer->cur_len >= buffer->malloc_len)
	{
		if (!(copy = ft_strdup(buffer->buffer)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_strdel(&buffer->buffer);
		buffer->malloc_len += LINE_SIZE;
		if (!(buffer->buffer = ft_strnew(buffer->malloc_len)))
			rl_err("42sh", "malloc() error", ENOMEM);
		ft_strcpy(buffer->buffer, copy);
		ft_strdel(&copy);
	}
}
