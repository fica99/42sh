/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:22:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 00:04:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_reading(t_readline *rl)
{
	char	c[LINE_MAX + 1];

	signal(SIGWINCH, &rl_win_handler);
	rl_write_prompt(rl->prompt, rl->env, rl->history);
	rl_start_cord_data(&rl->cord);
	while (READING)
	{
		rl_read_handler(c, STDIN_FILENO);
		rl_malloc_len(&rl->line, c);
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
	if ((nb = read(fd, c, LINE_MAX)) < 0)
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
	t_hash	**hash;
	size_t	size;

	hash = NULL;
	size = 0;
	if (rl->mode == VI)
	{
		hash = rl->vi_hash;
		size = VI_HASH_SIZE;
	}
	else if (rl->mode == READLINE)
	{
		hash = rl->rl_hash;
		size = RL_HASH_SIZE;
	}
	if (ft_isprint(*c))
	{
		if (g_rl_flags)
			rl_disable_line(rl);
		rl_print_symb(c, rl);
	}
	else if ((handler = get_hash_data(hash, c, size)))
		handler(rl);
}

