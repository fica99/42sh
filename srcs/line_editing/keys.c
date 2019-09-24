/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:13:53 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/26 22:17:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	k_left(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (is_start_pos(cord))
		return ;
	ft_putstr_fd(CUR_LFT, STDIN_FILENO);
	cord->pos--;
	if (--cord->x_cur < 0)
	{
		cord->x_cur = cord->ws_col - 1;
		cord->y_cur--;
	}
}

void	k_right(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (is_end_pos(cord))
		return ;
	ft_putstr_fd(CUR_RIGHT, STDIN_FILENO);
	cord->pos++;
	if (++cord->x_cur >= cord->ws_col)
	{
		cord->x_cur = 0;
		cord->y_cur++;
	}
}
