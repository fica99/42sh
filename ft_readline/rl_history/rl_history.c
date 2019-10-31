/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/31 22:43:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_make_history_buff(t_rl_history *history, char **env)
{
	int		fd;
	char	**buff;
	short	len;
	int		histsize;
	int		histfilesize;

	if (!(histsize = ft_atoi(rl_getenv("HISTSIZE", env))))
		histsize = RL_HISTSIZE;
	if (!(histfilesize = ft_atoi(rl_getenv("HISTFILESIZE", env))))
		histfilesize = RL_HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
	if (!(buff = ft_darnew(histsize)))
		rl_err("42sh", "malloc() error", ENOMEM);
	history->hisfile_path = rl_get_history_file_path(env);
	if ((fd = open(history->hisfile_path, RL_OPEN_HISTFILE,
	RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	len = 0;
	while (len != histsize && (get_next_line(fd, &buff[len]) > 0))
		++len;
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	history->hist_len = len;
	history->history_buff = buff;
}

void		rl_free_history(t_rl_history *history)
{
	char	**buf;

	rl_rewrite_file(history);
	buf = history->history_buff;
	ft_free_dar(buf);
	ft_strdel(&history->hisfile_path);
	history->history_buff = NULL;
	history->hist_len = 0;
}

void		rl_add_to_history_buff(char *buffer, t_rl_history *history)
{
	short	len;
	short	i;
	char	*nl;

	while ((nl = ft_strchr(buffer, '\n')))
	{
		*nl = '\0';
		rl_add_to_history_buff(buffer, history);
		buffer = nl + 1;
	}
	if (!*buffer)
		return ;
	len = history->hist_len;
	if (len >= history->histsize)
	{
		ft_memdel((void**)&(history->history_buff[0]));
		i = -1;
		while (++i < len - 1)
			history->history_buff[i] = history->history_buff[i + 1];
	}
	else
		i = ++history->hist_len;
	if (!(history->history_buff[i] = ft_strdup(buffer)))
		rl_err("42sh", "malloc() error", ENOMEM);
}

void		rl_rewrite_file(t_rl_history *history)
{
	int		fd;
	short	i;

	if ((fd = open(history->hisfile_path,
	RL_REWRITE_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	i = -1;
	if (history->histfilesize < history->hist_len)
		i += history->hist_len - history->histfilesize;
	while (++i < history->histsize)
		ft_putendl_fd(history->history_buff[i], fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
}

char		*rl_get_history_file_path(char **env)
{
	char	*home;

	if ((home = rl_getenv("HOME", env)))
		return (ft_strjoin(home, RL_HISTORY_FILE));
	return (NULL);
}
