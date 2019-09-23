/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:32:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/23 21:39:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	set_data(t_line *line)
{
	g_line_flags = INIT_FLAGS;
	get_win_size(line->cord);
	get_cur_cord(line->cord);
	set_start_cord(line->cord);
}

void		unset_data(t_line *line)
{
	unset_cord(line->cord);
	ft_strclr(line->buffer.buffer);
	ft_strclr(line->save_buff.buffer);
	ft_strclr(line->her_buff.buffer);
	ft_strclr(line->history_search.buffer);
}
