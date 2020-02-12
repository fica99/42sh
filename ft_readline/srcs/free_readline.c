/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:20:15 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/12 21:02:54 by aashara-         ###   ########.fr       */
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
