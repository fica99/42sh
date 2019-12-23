/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_hist_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:13:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_search_exp(char *line, t_rl_history history)
{
	int		i;
	char	*new_line;

	i = history.hist_len;
	new_line = NULL;
	while (--i >= 0)
	{
		if ((ft_strstr(history.history_buff[i], line)))
		{
			if (!(new_line = ft_strdup(history.history_buff[i])))
				rl_err("42sh", "malloc() error", UNDEFERR);
			break ;
		}
	}
	return (new_line);
}

char	*rl_digit_exp(int i, t_rl_history history)
{
	char	*line;

	line = NULL;
	if (i < 0)
		line = rl_hist_copy(history.hist_len + i, history.history_buff);
	else if (i > 0)
		line = rl_hist_copy(i, history.history_buff);
	return (line);
}

char	*rl_hist_copy(short index, char **hist_buff)
{
	char	*new_line;

	if (index < 0 || index >= get_hist_size())
		return (NULL);
	if (!(new_line = ft_strdup(hist_buff[index])))
		rl_err("42sh", "malloc() error", UNDEFERR);
	return (new_line);
}
