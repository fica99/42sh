/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_free_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:21:48 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/20 22:10:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_free_history(t_rl_history *history)
{
	int		fd;
	size_t	i;
	char	*histfile;

	if (!(histfile = get_env("HISTFILE", SET_ENV)))
		histfile = RL_HISTORY_FILE;
	rl_get_hist_size(history);
	if ((fd = open(histfile, RL_WRITE_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", NOERROR);
	i = 0;
	if (history->histfilesize < history->hist_len)
		i = history->hist_len - history->histfilesize;
	while (i < history->hist_len && history->history_buff[i])
		ft_putendl_fd(history->history_buff[i++], fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", NOERROR);
	ft_free_dar(history->history_buff);
}
