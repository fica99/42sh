/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_init_history(t_rl_history *history)
{
	size_t	len;
	char	path[RL_MAX_BUFF];
	char	*home;
	char	*rl_histsize;
	char	*rl_histfilesize;

	if ((home = get_env("HOME", ENV)))
		ft_strcat(ft_strcpy(path, home), RL_HISTORY_FILE);
	else
		ft_strcpy(path, RL_HISTORY_FILE);
	set_env("HISTFILE", path, SET_ENV);
	set_env("HISTSIZE", RL_HISTSIZE, SET_ENV);
	set_env("HISTFILESIZE", RL_HISTFILESIZE, SET_ENV);
	if ((rl_histsize = get_env("HISTSIZE", ENV)))
		set_env("HISTSIZE", rl_histsize, SET_ENV);
	if ((rl_histfilesize = get_env("HISTFILESIZE", ENV)))
		set_env("HISTFILESIZE", rl_histfilesize, SET_ENV);
	rl_get_hist_size(history);
	len = rl_find_hist_len(path);
	rl_set_hist_buff(path, history, len);
}

void	rl_get_hist_size(t_rl_history *history)
{
	history->histfilesize = ft_atoi(get_env("HISTFILESIZE", ALL_ENV));
	history->histsize = ft_atoi(get_env("HISTSIZE", ALL_ENV));
}

size_t	rl_find_hist_len(char *path)
{
	int		fd;
	int		res;
	size_t	len;
	char	*buff;

	if ((fd = open(path, RL_OPEN_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	len = 0;
	while ((res = get_next_line(fd, &buff)) > 0)
	{
		ft_strdel(&buff);
		++len;
	}
	if (res < 0)
		rl_err("42sh", "get_next_line() error", UNDEFERR);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	return (len);
}

void	rl_set_hist_buff(char *path, t_rl_history *history, size_t hist_len)
{
	size_t	len;
	int		fd;
	char	*buff;

	len = 0;
	if (!(history->history_buff = ft_darnew(history->histsize)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if ((fd = open(path, RL_OPEN_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	if (hist_len > history->histsize)
		len = hist_len - history->histsize;
	while (len && (get_next_line(fd, &buff) > 0))
	{
		ft_strdel(&buff);
		--len;
	}
	while (len != history->histsize &&
	(get_next_line(fd, &history->history_buff[len]) > 0))
		++len;
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	history->hist_len = len;
	history->hist_index = len;
}
