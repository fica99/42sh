/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:16:25 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/16 18:24:44 by aashara          ###   ########.fr       */
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
		err("42sh", "ft_readline",
		"Missing required sequences, possibly unexpected behavior", NOERROR);
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
	rl_save_mode(&g_rl.start_mode);
	rl_init_terminfo();
	rl_check_terminfo_templates();
	rl_init_readline_struct(&g_rl);
}
