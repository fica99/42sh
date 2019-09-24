/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:32:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/25 19:22:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		set_data(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	g_line_flags = INIT_FLAGS;
	get_win_size(cord);
	get_cur_cord(cord);
	set_start_cord(cord);
	set_end_cord(cord);
	if ((line->her_fd = open(HEREDOC_FILE, RRED_OPEN, PERM_MODE)) == -1)
		err_exit(g_argv[0], "open() error", NULL, NOERROR);
}

void		unset_data(t_line *line)
{
	unset_cord(line->cord);
	ft_strclr(line->buffer.buffer);
	ft_strclr(line->save_buff.buffer);
	ft_strclr(line->her_buff.buffer);
	ft_strclr(line->history_search.buffer);
	if (close(line->her_fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
}
