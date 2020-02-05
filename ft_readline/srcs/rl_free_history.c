/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_free_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:21:48 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 22:33:31 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_free_history(t_rl_history *history)
{
	int		fd;
	int		i;
	char	*histfile;

	if (!(histfile = get_var("HISTFILE", VARS)))
		histfile = RL_HISTORY_FILE;
	rl_get_hist_size(history);
	if ((fd = open(histfile, O_RDWR | O_TRUNC | O_CREAT,
												S_IRUSR | S_IWUSR)) == -1)
		rl_err("42sh", "open histfile error", NOERROR);
	i = 0;
	if (history->histfilesize < history->hist_len)
		i = history->hist_len - history->histfilesize;
	while (i < history->hist_len && history->history_buff[i])
		ft_putendl_fd(history->history_buff[i++], fd);
	if (close(fd) == -1)
		rl_err("42sh", "close histfile error", NOERROR);
	ft_free_dar(history->history_buff);
}
