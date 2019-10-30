/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:22:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/30 18:25:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_reading(t_readline *rl)
{
	char	c[LINE_MAX + 1];

	ft_putstr_fd(rl->prompt, STDOUT_FILENO);
	rl_start_cord_data(&rl->cord);
	rl_print(rl->line.buffer + rl->cord.pos, &rl->cord);
	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		rl_malloc_len(&rl->line, c);
		rl_find_template(rl, c);
		if (g_rl_flags & RL_BREAK_FLAG)
			break ;
	}
	return (rl->line.buffer);
}

void	read_handler(char *c, int fd)
{
	short	nb;

	ft_putstr_fd(TRANSMIT_MODE, STDIN_FILENO);
	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
		rl_err("42sh", "read() error", UNDEFERR);
	}
	c[nb] = '\0';
	ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
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
	if ((handler = get_hash_data(hash, c, size)))
		handler(rl);
}

