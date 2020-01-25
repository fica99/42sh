/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:44:51 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 16:07:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static size_t	rl_find_hist_len(char *path)
{
	int		fd;
	int		res;
	int		len;
	char	*buff;

	if ((fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		rl_err("42sh", "open() error", NOERROR);
	len = 0;
	while ((res = get_next_line(fd, &buff)) > 0)
	{
		ft_strdel(&buff);
		++len;
	}
	if (res < 0)
		rl_err("42sh", "get_next_line() error", NOERROR);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", NOERROR);
	return (len);
}

static void		rl_set_hist_buff(char *path, t_rl_history *history,
														int hist_len)
{
	int		len;
	int		fd;
	char	*buff;

	len = 0;
	if (!(history->history_buff = ft_darnew(history->histsize)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if ((fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		rl_err("42sh", "open() error", NOERROR);
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
		rl_err("42sh", "close() error", NOERROR);
	history->hist_len = len;
	history->hist_index = len;
	history->cur_command_nb = 0;
}

void			rl_init_history(t_rl_history *history)
{
	char	*path;
	char	*rl_histsize;
	char	*rl_histfilesize;

	if ((get_env("HOME", ENV)))
	{
		if (!(path = ft_strjoin(get_env("HOME", ENV), RL_HISTORY_FILE)))
			rl_err("42sh", "malloc() error", ENOMEM);
	}
	else if (!(path = ft_strdup(RL_HISTORY_FILE)))
		rl_err("42sh", "malloc() error", ENOMEM);
	set_env("HISTFILE", path, SET_ENV);
	if (!(rl_histsize = get_env("HISTSIZE", ALL_ENV)))
	{
		rl_histsize = RL_HISTSIZE;
		set_env("HISTSIZE", rl_histsize, SET_ENV);
	}
	if (!(rl_histfilesize = get_env("HISTFILESIZE", ALL_ENV)))
	{
		rl_histfilesize = RL_HISTFILESIZE;
		set_env("HISTFILESIZE", rl_histfilesize, SET_ENV);
	}
	rl_get_hist_size(history);
	rl_set_hist_buff(path, history, rl_find_hist_len(path));
	ft_strdel(&path);
}
