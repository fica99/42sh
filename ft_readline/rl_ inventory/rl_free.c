/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:54:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/31 22:37:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_free_rl_struct(t_readline *rl)
{
	rl_free_buff(&rl->line);
	rl_free_buff(&rl->save_line);
	rl_free_buff(&rl->copy_buff);
	rl_init_cord(&rl->cord);
	rl->vi_hash = free_hash_table(rl->vi_hash, VI_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl->rl_hash = free_hash_table(rl->rl_hash, RL_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl_free_history(&rl->history);
}

void	rl_free_buff(t_rl_buff *buffer)
{
	if (buffer)
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
}

void		rl_clr_data(t_readline *rl)
{
	ft_strclr(rl->line.buffer);
	ft_strclr(rl->save_line.buffer);
	rl_init_cord(&rl->cord);
	g_rl_flags = RL_INIT_FLAGS;
}
