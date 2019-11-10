/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:56 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/10 19:58:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_get_hist_size(t_rl_history *history, char **env)
{
	int		histsize;
	int		histfilesize;

	if (!(histsize = ft_atoi(ft_getenv("HISTSIZE", env))))
		histsize = RL_HISTSIZE;
	if (!(histfilesize = ft_atoi(ft_getenv("HISTFILESIZE", env))))
		histfilesize = RL_HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
}

char		*rl_get_history_file_path(char **env)
{
	char	*home;

	if ((home = ft_getenv("HOME", env)))
		return (ft_strjoin(home, RL_HISTORY_FILE));
	return (ft_strjoin("/", RL_HISTORY_FILE));
}

void		rl_check_history_size(t_rl_history *history, char **env)
{
	int	histsize;

	histsize = history->histsize;
	rl_get_hist_size(history, env);
	if (histsize != history->histsize)
	{
		ft_free_dar(history->history_buff);
		history->history_buff = NULL;
		history->hist_len = 0;
		rl_make_history_buff(history);
	}
}

void		rl_make_history_buff(t_rl_history *history)
{
	int		fd;
	char	**buff;
	short	len;

	if (!(buff = ft_darnew(history->histsize)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if ((fd = open(history->histfile_path, RL_OPEN_HISTFILE,
	RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	len = 0;
	while (len != history->histsize && (get_next_line(fd, &buff[len]) > 0))
		++len;
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	history->hist_len = len;
	history->hist_index = len;
	history->history_buff = buff;
	history->cur_command_nb = 1;
}
