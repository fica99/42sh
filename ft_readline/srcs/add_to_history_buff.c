/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history_buff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:47:49 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/23 21:53:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_get_hist_size(t_rl_history *history)
{
	if ((history->histfilesize = ft_atoi(get_env("HISTFILESIZE", SET_ENV))) < 0)
		history->histfilesize = 0;
	if ((history->histsize = ft_atoi(get_env("HISTSIZE", SET_ENV))) < 0)
		history->histsize = 0;
}

void	rl_check_history_size(t_rl_history *history)
{
	int	histsize;

	histsize = history->histsize;
	rl_get_hist_size(history);
	if (histsize != history->histsize)
	{
		rl_free_history(history);
		rl_init_history(history);
	}
}

char	rl_is_all_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	add_to_history_buff(char *line)
{
	int			i;
	char		*nl;

	rl_check_history_size(&g_rl.history);
	if (!line || !*line || !g_rl.history.histsize)
		return ;
	while ((nl = ft_strchr(line, '\n')))
	{
		*nl = '\0';
		add_to_history_buff(line);
		line = nl + 1;
	}
	if (rl_is_all_spaces(line))
		return ;
	if (g_rl.history.hist_len >= g_rl.history.histsize)
	{
		ft_memdel((void**)&(g_rl.history.history_buff[0]));
		i = -1;
		while (++i < g_rl.history.hist_len - 1)
			g_rl.history.history_buff[i] = g_rl.history.history_buff[i + 1];
	}
	else
		i = g_rl.history.hist_len++;
	if (!(g_rl.history.history_buff[i] = ft_strdup(line)))
		rl_err("42sh", "malloc() error", ENOMEM);
}
