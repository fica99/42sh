/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:04:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/20 00:22:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_init_history(t_rl_history *history, char **env)
{
	short	len;
	char	path[RL_MAX_BUFF];
	char	*home;

	if ((home = ft_getenv("HOME", env)))
		ft_strcat(ft_strcat(ft_strcpy(path, home), "/"), RL_HISTORY_FILE);
	else
		ft_strcat(ft_strcpy(path, "/"), RL_HISTORY_FILE);
	rl_get_hist_size(history, env);
	len = rl_find_hist_len(path);
	rl_set_hist_buff(path, history, len);
}

short	rl_find_hist_len(char *path)
{
	int		fd;
	int		res;
	short	len;
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

void	rl_set_hist_buff(char *path, t_rl_history *history, short hist_len)
{
	short	len;
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
		len--;
	}
	while (len != history->histsize &&
	(get_next_line(fd, &history->history_buff[len]) > 0))
		++len;
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	history->hist_len = len;
	history->hist_index = len;
}
