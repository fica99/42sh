/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:18:56 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 21:23:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_readline(char *prompt, t_rl_mode mode)
{
	char	*buff;

	g_rl.mode = mode;
	g_rl.prompt = prompt;
	rl_write_prompt(g_rl.prompt, g_rl.history);
	rl_clr_data(&g_rl);
	if (!(buff = ft_strdup(rl_reading(&g_rl))))
		rl_err("42sh", "malloc() error", ENOMEM);
	return (buff);
}

void	init_readline(void)
{
	rl_save_attr(&g_rl.canon_mode);
	rl_init_terminfo();
	if (!RL_TRANSMIT_MODE || !RL_CUR_CORD || !RL_STOP_TRANSMIT_MODE ||
	!RL_SET_CUR || !RL_K_LFT || !RL_K_RGHT || !RL_K_HOME || !RL_K_END ||
	!RL_SHIFT_LEFT || !RL_SHIFT_RIGHT || !RL_CUR_VIS || !RL_CUR_INVIS ||
	!RL_CLEAR_END_SCREEN || !RL_K_DEL || !RL_K_DOWN || !RL_K_UP
	|| !RL_CLEAR_SCREEN)
		rl_err("42sh", "no correct capabilities", UNDEFERR);
	set_env("PS1", "\033[0;36m\\u\033[0;31m@\033[0;32m\\H\033[0;31m:\033[0;33m\\w\n\033[0;35m\\$> \033[0m", SET_ENV);
	set_env("PS2", "> ", SET_ENV);
	set_env("PS4", "+ ", SET_ENV);
	rl_init_rl_struct(&g_rl);
}

void	free_readline(void)
{
	reset_shell_mode();
	rl_set_attr(&g_rl.canon_mode);
	rl_free_rl_struct(&g_rl);
}

void	add_to_history_buff(char *line)
{
	size_t			len;
	size_t			i;

	rl_check_history_size(&g_rl.history);
	if (!line || !*line)
		return ;
	++g_rl.history.cur_command_nb;
	len = g_rl.history.hist_len;
	if (g_rl.history.histsize)
	{
		if (len >= g_rl.history.histsize)
		{
			ft_memdel((void**)&(g_rl.history.history_buff[0]));
			i = -1;
			while (++i < len - 1)
				g_rl.history.history_buff[i] = g_rl.history.history_buff[i + 1];
		}
		else
			i = g_rl.history.hist_len++;
		if (!(g_rl.history.history_buff[i] = ft_strdup(line)))
			rl_err("42sh", "malloc() error", ENOMEM);
	}
}

char	*get_hist_expansions(char *line)
{
	char	*new_line;

	new_line = NULL;
	if (line && *line)
	{
		if ((line[0] == '-' && ft_isdigit(line[1]))
		|| ft_isdigit(line[0]))
			new_line = rl_digit_exp(ft_atoi(line), g_rl.history);
		else if (ft_strlen(line) == 1 && line[0] == '!')
			new_line = rl_digit_exp(-1, g_rl.history);
		else
			new_line = rl_search_exp(line, g_rl.history);
	}
	return (new_line);
}
