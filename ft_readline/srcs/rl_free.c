/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:54:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/12 21:51:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_free_rl_struct(t_readline *rl)
{
	rl->vi_hash = free_hash_table(rl->vi_hash, VI_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl->rl_hash = free_hash_table(rl->rl_hash, EMACS_HASH_SIZE,
	DONT_FREE_HASH_DATA);
	rl_free_history(&rl->history, rl->env);
}

void		rl_clr_data(t_readline *rl)
{
	*rl->line = '\0';
	*rl->history.save_line = '\0';
	*rl->history.search = '\0';
	*rl->save_line = '\0';
	rl_init_cord(&rl->cord);
	g_rl_flags = RL_INIT_FLAGS;
	rl->history.hist_index = rl->history.hist_len;
}
