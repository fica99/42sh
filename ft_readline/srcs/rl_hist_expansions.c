/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_hist_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:13:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/20 23:13:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_hist_expansions(char *line)
{
	char	*new_line;

	new_line = NULL;
	if (line && *line)
	{
		if (ft_atoi(line))
			new_line = rl_digit_exp(ft_atoi(line), &g_rl.history);
		else if (ft_strlen(line) && *line == '!')
			new_line = rl_digit_exp(-1, &g_rl.history);
		else
			new_line = rl_search_exp(-1, &g_rl.history);
	}
	return (new_line);
}

char	*rl_search_exp(char *line, t_rl_history *history)
{

}

char	*rl_digit_exp(int i, t_rl_history *history)
{
	char	*line;

	line = NULL;
	if (i < 0)
		line = rl_hist_exp(history->hist_len + i - 1, history->history_buff);
	else if (i > 0)
		line = rl_hist_exp(i, history->history_buff);
	return (line);
}

char	*rl_hist_exp(short index, char **hist_buff)
{
	char	*new_line;

	if (index < 0)
		return (NULL);
	if (!(new_line = ft_strdup(hist_buff[index])))
		rl_err("42sh", "malloc() error", UNDEFERR);
	return (new_line);
}
