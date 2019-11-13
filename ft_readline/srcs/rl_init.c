/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:14:25 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/13 17:49:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_init_terminfo(void)
{
	int		err;

	if (!isatty(STDIN_FILENO))
		rl_err("42sh", "stdin is not a terminal", UNDEFERR);
	if ((setupterm(0, STDIN_FILENO, &err) == ERR))
	{
		if (err == 1)
			rl_err("42sh", "setupterm() error", EHRDCPY);
		else if (err == 0)
			rl_err("42sh", "setupterm() error", ENTFND);
		else if (err == -1)
			rl_err("42sh", "setupterm() error", ENOTERMINFO);
	}
}

void		rl_init_rl_struct(t_readline *rl, char **env)
{
	rl->vi_hash = init_vi_hash(VI_HASH_SIZE);
	rl->rl_hash = init_emacs_hash(EMACS_HASH_SIZE);
	rl_init_cord(&rl->cord);
	ft_bzero((void*)rl->line, MAX_LINE_SIZE);
	ft_bzero((void*)rl->copy_buff, MAX_LINE_SIZE);
	ft_bzero((void*)rl->save_line, MAX_LINE_SIZE);
	rl_init_history(&rl->history, env);
	g_rl_flags = RL_INIT_FLAGS;
}

void		rl_init_cord(t_rl_cord *cord)
{
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->highlight_pos = 0;
	cord->x_end = 0;
	cord->y_end = 0;
}
