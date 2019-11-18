/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:52:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 19:06:00 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_x_upper(t_readline *rl)
{
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_v(t_readline *rl)
{
	int		fd;
	char	*buff;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if ((fd = open(RL_VIFILE, RL_OPEN_VIFILE, RL_PERM_VIFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	ft_putstr_fd(rl->line.buffer, fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	rl_open_editor(rl->env);
	ft_strclr(rl->line.buffer);
	if ((fd = open(RL_VIFILE, RL_READ_VIFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	while (get_next_line(fd, &buff) > 0)
	{
		rl_check_str_mem(&rl->line, buff);
		ft_strcat(rl->line.buffer, buff);
		ft_strdel(&buff);
	}
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	rl_k_enter(rl);
}
