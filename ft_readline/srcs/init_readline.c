/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:16:25 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 13:18:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	rl_init_terminfo(void)
{
	int	err;

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

static void	rl_check_terminfo_templates(void)
{
	if (!RL_TRANSMIT_MODE || !RL_CUR_CORD || !RL_STOP_TRANSMIT_MODE ||
	!RL_SET_CUR || !RL_K_LFT || !RL_K_RGHT || !RL_K_HOME || !RL_K_END ||
	!RL_SHIFT_LEFT || !RL_SHIFT_RIGHT || !RL_CUR_VIS || !RL_CUR_INVIS ||
	!RL_CLEAR_END_SCREEN || !RL_K_DEL || !RL_K_DOWN || !RL_K_UP
	|| !RL_CLEAR_SCREEN)
		rl_err("42sh", "no correct capabilities", UNDEFERR);
}

static void	rl_init_readline_struct(t_readline *rl)
{
	rl_init_cord(&rl->cord);
	rl->emacs_temp = init_emacs_temp(EMACS_HASH_SIZE);
	rl->vi_temp = init_vi_temp(VI_HASH_SIZE);
	rl_init_history(&rl->history);
	rl_init_buff(&rl->history.save_line);
	rl_init_buff(&rl->history.search);
	rl_init_buff(&rl->line);
	rl_init_buff(&rl->copy_buff);
	rl_init_buff(&rl->save_line);
}

void		init_readline(void)
{
	char	*ps1;
	char	*ps2;
	char	*ps4;

	rl_save_mode(&g_rl.start_mode);
	rl_init_terminfo();
	rl_check_terminfo_templates();
	if (!(ps1 = get_env("PS1", ALL_ENV)))
		ps1 = "\033[0;36m\\u\033[0;31m@\033[0;32m\\H\033[0;31m:\033[0;33m\\w\n\033[0;35m\\$> \033[0m";
	set_env("PS1", ps1, SET_ENV);
	if (!(ps2 = get_env("PS2", ALL_ENV)))
		ps2 = "> ";
	set_env("PS2", ps2, SET_ENV);
	if (!(ps4 = get_env("PS4", ALL_ENV)))
		ps4 = "+ ";
	set_env("PS4", ps4, SET_ENV);
	rl_init_readline_struct(&g_rl);
}
