/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:20:15 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 17:16:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_clr_data(t_readline *rl)
{
	rl_clr_buff(&rl->line);
	rl_clr_buff(&rl->save_line);
	rl_clr_buff(&rl->history.save_line);
	rl_clr_buff(&rl->history.search);
	rl_init_cord(&rl->cord);
	g_rl_flags = RL_INIT_FLAGS;
}

void		rl_clr_buff(t_buff *buff)
{
	ft_strclr(buff->buffer);
	buff->cur_len = 0;
}

static void	rl_free_readline_struct(t_readline *rl)
{
	rl->vi_temp = free_hash_table(rl->vi_temp, VI_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl->emacs_temp = free_hash_table(rl->emacs_temp, EMACS_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl_free_history(&rl->history);
	ft_strdel(&rl->history.save_line.buffer);
	ft_strdel(&rl->history.search.buffer);
	ft_strdel(&rl->line.buffer);
	ft_strdel(&rl->save_line.buffer);
	ft_strdel(&rl->copy_buff.buffer);
}

void		free_readline(void)
{
	reset_shell_mode();
	rl_set_mode(&g_rl.start_mode);
	rl_free_readline_struct(&g_rl);
}
