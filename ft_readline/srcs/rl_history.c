/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/20 20:35:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_free_history(t_rl_history *history, char **env)
{
	int		fd;
	short	i;
	char	path[RL_MAX_BUFF];
	char	*home;

	if ((home = ft_getenv("HOME", env)))
		ft_strcat(ft_strcat(ft_strcpy(path, home), "/"), RL_HISTORY_FILE);
	else
		ft_strcat(ft_strcpy(path, "/"), RL_HISTORY_FILE);
	rl_get_hist_size(history, env);
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

void		rl_add_to_history_buff(char *buffer, t_rl_history *history)
{
	short	len;
	short	i;

	if (!buffer || !*buffer)
		return ;
	len = history->hist_len;
	if (history->histsize)
	{
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
	}
}

void		rl_get_hist_size(t_rl_history *history, char **env)
{
	int		histsize;
	int		histfilesize;
	char	*rl_histsize;
	char	*rl_histfilesize;

	if (!(rl_histsize = ft_getenv("HISTSIZE", env)))
		histsize = RL_HISTSIZE;
	else
		histsize = ft_atoi(rl_histsize);
	if (!(rl_histfilesize = ft_getenv("HISTFILESIZE", env)))
		histfilesize = RL_HISTFILESIZE;
	else
		histfilesize = ft_atoi(rl_histfilesize);
	if (histfilesize < 0)
		histfilesize = 0;
	if (histsize <= 0)
		histsize = 1;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
}

void		rl_check_history_size(t_rl_history *history, char **env)
{
	int	histsize;

	histsize = history->histsize;
	rl_get_hist_size(history, env);
	if (histsize != history->histsize)
	{
		rl_free_history(history, env);
		rl_init_history(history, env);
	}
}
