/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:02:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/26 23:16:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	print_symb(char *c, t_line *line)
{
	t_cord	*cord;
	short	len;

	if (ft_isprint(*c))
	{
		ft_putstr_fd(ENTER_INSERT_MODE, STDIN_FILENO);
		cord = line->cord;
		ft_stradd(line->buffer.buffer, c, cord->pos);
		len = ft_strlen(c);
		cord->pos += len;
		cord->x_cur += len;
		if (cord->x_cur >= cord->ws_col)
		{
			cord->x_cur = 0;
			if (cord->y_cur >= cord->ws_row - 1)
				cord->y_start--;
			else
				cord->y_cur++;
		}
		ft_putstr_fd(c, STDIN_FILENO);
		ft_putstr_fd(EXIT_INSERT_MODE, STDIN_FILENO);
	}
}
