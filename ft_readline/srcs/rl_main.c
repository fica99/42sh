/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:18:56 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 20:55:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_readline(char *prompt, t_rl_mode mode, char **environ)
{
	char	*buff;

	g_rl.mode = mode;
	g_rl.env = environ;
	g_rl.prompt = prompt;
	rl_check_history_size(&g_rl.history, environ);
	rl_clr_data(&g_rl);
	rl_set_non_canon_mode(&g_rl.non_canon_mode);
	if (!(buff = ft_strdup(rl_reading(&g_rl))))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_set_attr(&g_rl.canon_mode);
	if (!rl_check_empty_line(buff))
		ft_strdel(&buff);
	rl_add_to_history_buff(buff, &g_rl.history);
	rl_clr_data(&g_rl);
	return (buff);
}

void	init_readline(char **environ)
{
	rl_save_attr(&g_rl.canon_mode);
	rl_init_terminfo();
	if (!RL_TRANSMIT_MODE || !RL_CUR_CORD || !RL_STOP_TRANSMIT_MODE ||
	!RL_SET_CUR || !RL_K_LFT || !RL_K_RGHT || !RL_K_HOME || !RL_K_END ||
	!RL_SHIFT_LEFT || !RL_SHIFT_RIGHT || !RL_CUR_VIS || !RL_CUR_INVIS ||
	!RL_CLEAR_END_SCREEN || !RL_K_DEL || !RL_K_DOWN || !RL_K_UP)
		rl_err("42sh", "no correct capabilities", UNDEFERR);
	rl_init_rl_struct(&g_rl, environ);
}

void	free_readline(void)
{
	reset_shell_mode();
	rl_set_attr(&g_rl.canon_mode);
	rl_free_rl_struct(&g_rl);
}

void	rl_err(char *name, char *str, char *err)
{
	ft_putstr_fd(name, STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	if (err)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_set_attr(&g_rl.canon_mode);
	exit(EXIT_FAILURE);
}
