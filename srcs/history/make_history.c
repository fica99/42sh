/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 19:26:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		make_history_buff(t_history *history)
{
	int		fd;
	char	**buff;
	short	len;
	int		histsize;
	int		histfilesize;

	if ((fd = open(HISTORY_FILE, OPEN_HISTFILE, PERM_HISTFILE)) == -1)
		err_exit(g_argv[0], "open() error", NULL, NOERROR);
	history->hist_fd = fd;
	if (!(histsize = ft_atoi(ft_getenv("HISTSIZE"))))
		histsize = HISTSIZE;
	if (!(histfilesize = ft_atoi(ft_getenv("HISTFILESIZE"))))
		histfilesize = HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
	if (!(buff = ft_darnew(histsize)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	len = 0;
	while (len != histsize && (get_next_line(fd, &buff[len]) > 0))
		len++;
	history->hist_len = len;
	history->history_buff = buff;
}

void	free_history(t_history *history)
{
	char	**buf;

	buf = history->history_buff;
	history->history_index = -1;
	if (close(history->hist_fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
	ft_free_dar(buf);
	history->history_buff = NULL;
	history->hist_len = 0;
}
