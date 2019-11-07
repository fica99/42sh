/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_find_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:43:20 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/07 23:19:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_find_history(t_readline *rl)
{
	int		index;
	char	*history_buffer;

	if (!(*rl->hist_search.buffer))
		return ;
	index = rl->history.hist_index;
	while (--index >= 0)
	{
		history_buffer = rl->history.history_buff[index];
		if (ft_strstr(history_buffer, rl->hist_search.buffer))
		{
			rl->history.hist_index = index;
			rl_malloc_len(&rl->line, history_buffer);
			ft_strcpy(rl->line.buffer + rl->cord.pos, history_buffer);
		}
	}
}
