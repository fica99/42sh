/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history_buff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:47:49 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/08 18:01:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	add_to_history_buff(char *line)
{
	size_t			i;
	char			*nl;

	if (!line || !*line)
		return ;
	rl_check_history_size(&g_rl.history);
	if (!g_rl.history.histsize)
		return ;
	while ((nl = ft_strchr(line, '\n')))
	{
		*nl = '\0';
		add_to_history_buff(line);
		line = nl + 1;
	}
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
