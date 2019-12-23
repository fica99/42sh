/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:54:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_free_rl_struct(t_readline *rl)
{
	rl->vi_hash = free_hash_table(rl->vi_hash, VI_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl->rl_hash = free_hash_table(rl->rl_hash, EMACS_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl->noedit_hash = free_hash_table(rl->noedit_hash, NOEDIT_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl_free_history(&rl->history);
	ft_strdel(&rl->line.buffer);
	ft_strdel(&rl->save_line.buffer);
	ft_strdel(&rl->copy_buff.buffer);
	ft_strdel(&rl->history.save_line.buffer);
	ft_strdel(&rl->history.search.buffer);
}

void		rl_clr_data(t_readline *rl)
{
	rl_clr_buff(&rl->line);
	rl_clr_buff(&rl->save_line);
	rl_clr_buff(&rl->history.save_line);
	rl_clr_buff(&rl->history.search);
	rl_init_cord(&rl->cord);
	g_rl_flags = RL_INIT_FLAGS;
	rl->history.hist_index = rl->history.hist_len;
}

void		rl_clr_buff(t_buff *buff)
{
	ft_strclr(buff->buffer);
	buff->max_len = 0;
}
