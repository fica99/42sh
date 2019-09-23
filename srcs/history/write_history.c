/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:21:43 by filip             #+#    #+#             */
/*   Updated: 2019/09/23 22:26:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		add_to_history(char *buffer, t_history *history)
{
	short	len;
	short	i;

	len = history->hist_len;
	if (len >= history->histsize)
	{
		i = -1;
		ft_memdel((void**)&(history->history_buff[0]));
		while (++i < len - 1)
			history->history_buff[i] = history->history_buff[i + 1];
		if (!(history->history_buff[i] = ft_strdup(buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if (!(history->history_buff[len++] = ft_strdup(buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
		history->hist_len++;
	}
	history->history_buff[len] = NULL;
}

void		write_history(char *buffer, t_history *history)
{
	short	len;

	add_to_history(buffer, history);
	len = history->hist_len;
	len < history->histfilesize ? add_to_file(len, history) :
	rewrite_file(len, history);
}

void		rewrite_file(short len, t_history *history)
{
	int		fd;
	short	i;

	fd = history->hist_fd;
	i = -1;
	while (++i < len)
	{
		ft_putstr_fd(history->history_buff[i], fd);
		ft_putchar_fd('\n', fd);
	}
}

void		add_to_file(short len, t_history *history)
{
	int		fd;

	fd = history->hist_fd;
	ft_putstr_fd(history->history_buff[len - 1], fd);
	ft_putchar_fd('\n', fd);
}
