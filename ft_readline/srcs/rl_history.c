/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/07 23:37:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

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
	history->history_buff = buff;
	history->cur_command_nb = 1;
}

void		rl_free_history(t_rl_history *history)
{
	char	**buf;

	rl_rewrite_file(history);
	buf = history->history_buff;
	ft_free_dar(buf);
	ft_strdel(&history->histfile_path);
	history->history_buff = NULL;
}

void		rl_add_to_history_buff(char *buffer, t_rl_history *history)
{
	short	len;
	short	i;

	if (!buffer || !*buffer)
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
		i = history->hist_len++;
	if (!(history->history_buff[i] = ft_strdup(buffer)))
		rl_err("42sh", "malloc() error", ENOMEM);
	++history->cur_command_nb;
}

void		rl_rewrite_file(t_rl_history *history)
{
	int		fd;
	short	i;

	if ((fd = open(history->histfile_path,
	RL_REWRITE_HISTFILE, RL_PERM_HISTFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	i = 0;
	if (history->histfilesize < history->hist_len)
		i += history->hist_len - history->histfilesize;
	while (i < history->histsize && history->history_buff[i])
		ft_putendl_fd(history->history_buff[i++], fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
}

void	rl_check_history_size(t_rl_history *history, char **env)
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
	history->hist_index = history->hist_len;
}
