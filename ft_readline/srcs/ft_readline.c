/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 17:46:05 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 17:54:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	win_handler(int sign)
{
	short	pos;

	if (sign == SIGWINCH)
	{
		g_rl_flags = RL_INIT_FLAGS;
		pos = g_rl.cord.pos;
		rl_set_mode(&g_rl.start_mode);
		ft_putchar('\n');
		ft_putstr(tigetstr("ed"));
		rl_write_prompt(g_rl.prompt, g_rl.history);
		rl_set_non_canon_mode(&g_rl.non_canon_mode);
		rl_start_cord_data(&g_rl.cord);
		rl_print(g_rl.line.buffer + g_rl.cord.pos, &g_rl.cord);
		rl_go_left(g_rl.cord.pos - pos, &g_rl.cord);
	}
}

static void	rl_find_template(t_readline *rl, char *c)
{
	void	(*handler)(t_readline *rl);

	if (rl->mode == VI)
	{
		if (ft_isprint(*c) && !(g_rl_flags & RL_VI_COMMAND_MODE))
			rl_print_symb(c, rl);
		else if ((handler = get_hash_data(rl->vi_temp, c, VI_HASH_SIZE)))
			handler(rl);
	}
	else if (rl->mode == EMACS)
	{
		if (ft_isprint(*c))
			rl_print_symb(c, rl);
		else if ((handler = get_hash_data(rl->emacs_temp, c, EMACS_HASH_SIZE)))
			handler(rl);
	}
}

static char	*rl_reading(t_readline *rl)
{
	char	c[RL_MAX_BUFF + 1];

	rl_set_non_canon_mode(&rl->non_canon_mode);
	rl_start_cord_data(&rl->cord);
	if (rl->mode == VI)
		g_rl_flags |= RL_VI_INPUT_MODE;
	while (READING)
	{
		signal(SIGWINCH, win_handler);
		rl_read_handler(c, STDIN_FILENO);
		rl_find_template(rl, c);
		if (g_rl_flags & RL_BREAK_FLAG)
			break ;
	}
	rl_set_mode(&g_rl.start_mode);
	return (rl->line.buffer);
}

char		*ft_readline(char *prompt)
{
	char	*buff;
	char	*mode;

	mode = get_env("READMODE", SET_ENV);
	if (ft_strcmp(mode, "VI"))
		g_rl.mode = VI;
	else
		g_rl.mode = EMACS;
	g_rl.prompt = prompt;
	rl_write_prompt(g_rl.prompt, g_rl.history);
	rl_clr_data(&g_rl);
	g_rl.history.hist_index = g_rl.history.hist_len;
	++g_rl.history.cur_command_nb;
	if (!(buff = ft_strdup(rl_reading(&g_rl))))
		rl_err("42sh", "malloc() error", ENOMEM);
	return (buff);
}

void		rl_read_handler(char *c, int fd)
{
	short	nb;

	ft_putstr_fd(tigetstr("smkx"), STDOUT_FILENO);
	while ((nb = read(fd, c, RL_MAX_BUFF)) == 0)
		continue ;
	if (nb < 0)
		rl_err("42sh", "read() error", NOERROR);
	c[nb] = '\0';
	ft_putstr_fd(tigetstr("rmkx"), STDOUT_FILENO);
}
