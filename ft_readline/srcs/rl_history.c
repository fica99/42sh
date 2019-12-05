/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 21:29:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_free_history(t_rl_history *history)
{
	int		fd;
	size_t	i;
	char	path[RL_MAX_BUFF];
	char	*histfile;

	if ((histfile = get_env("HISTFILE", SET_ENV)))
		ft_strcpy(path, histfile);
	else
		ft_strcpy(path, RL_HISTORY_FILE);
	rl_get_hist_size(history);
	if ((fd = open(path, RL_REWRITE_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	i = 0;
	if (history->histfilesize < history->hist_len)
		i = history->hist_len - history->histfilesize;
	while (i < history->hist_len && history->history_buff[i])
		ft_putendl_fd(history->history_buff[i++], fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	ft_free_dar(history->history_buff);
}

void		rl_check_history_size(t_rl_history *history)
{
	size_t	histsize;

	histsize = history->histsize;
	rl_get_hist_size(history);
	if (histsize != history->histsize)
	{
		rl_free_history(history);
		rl_init_history(history);
	}
}
