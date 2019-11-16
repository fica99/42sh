/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:22:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 18:34:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_reading(t_readline *rl)
{
	char	c[RL_MAX_BUFF + 1];

	signal(SIGWINCH, &rl_win_handler);
	rl_write_prompt(rl->prompt, rl->env, rl->history);
	rl_start_cord_data(&rl->cord);
	while (READING)
	{
		rl_read_handler(c, STDIN_FILENO);
		rl_find_template(rl, c);
		if (g_rl_flags & RL_BREAK_FLAG)
			break ;
	}
	return (rl->line.buffer);
}

void	rl_read_handler(char *c, int fd)
{
	short	nb;

	ft_putstr_fd(RL_TRANSMIT_MODE, STDOUT_FILENO);
	if ((nb = read(fd, c, RL_MAX_BUFF)) < 0)
	{
		ft_putstr_fd(RL_STOP_TRANSMIT_MODE, STDOUT_FILENO);
		rl_err("42sh", "read() error", UNDEFERR);
	}
	c[nb] = '\0';
	ft_putstr_fd(RL_STOP_TRANSMIT_MODE, STDOUT_FILENO);
}

void	rl_find_template(t_readline *rl, char *c)
{
	void	(*handler)(t_readline *rl);

	if (ft_isprint(*c))
		rl_print_symb(c, rl);
	else
	{
		if (rl->mode == VI)
			handler = get_hash_data(rl->vi_hash, c, VI_HASH_SIZE);
		else
			handler = get_hash_data(rl->rl_hash, c, EMACS_HASH_SIZE);
		if (handler)
			handler(rl);
	}
}
