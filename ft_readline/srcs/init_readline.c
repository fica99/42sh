/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:16:25 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 17:01:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	rl_init_terminfo(void)
{
	int	err;

	if (!isatty(STDIN_FILENO))
		rl_err("42sh", "stdin is not a terminal", NOERROR);
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
	if (!tigetstr("smkx") || !tigetstr("u7") || !tigetstr("rmkx") ||
	!tigetstr("cup") || !tigetstr("kcub1") || !tigetstr("kcuf1") ||
	!tigetstr("khome") || !tigetstr("kend") || !tigetstr("kLFT") ||
	!tigetstr("kRIT") || !tigetstr("cvvis") || !tigetstr("civis") ||
	!tigetstr("ed") || !tigetstr("kdch1") || !tigetstr("kcud1") ||
	!tigetstr("kcuu1") || !tigetstr("clear"))
		rl_err("42sh", "no correct capabilities", NOERROR);
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

	rl_save_mode(&g_rl.start_mode);
	rl_init_terminfo();
	rl_check_terminfo_templates();
	if (!(ps1 = get_env("PS1", ALL_ENV)))
		ps1 = "\033[0;36m\\u \033[0;32m\\H \033[0;33m\\w\n\033[0m\\$> ";
	set_env("PS1", ps1, SET_ENV);
	if (!(ps2 = get_env("PS2", ALL_ENV)))
		ps2 = "> ";
	set_env("PS2", ps2, SET_ENV);
	set_env("READMODE", "EMACS", SET_ENV);
	rl_init_readline_struct(&g_rl);
}
