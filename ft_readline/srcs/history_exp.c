/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:05:44 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/06 14:32:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*rl_search_exp(char *line, t_rl_history history)
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
				rl_err("42sh", "malloc() error", ENOMEM);
			break ;
		}
	}
	return (new_line);
}

static char	*rl_hist_copy(short index, char **hist_buff)
{
	char	*new_line;

	if (index < 0 || index >= (short)get_hist_size())
		return (NULL);
	if (!(new_line = ft_strdup(hist_buff[index])))
		rl_err("42sh", "malloc() error", ENOMEM);
	return (new_line);
}

static char	*rl_digit_exp(int i, t_rl_history history)
{
	char	*line;

	line = NULL;
	if (i < 0)
		line = rl_hist_copy(history.hist_len + i, history.history_buff);
	else if (i > 0)
		line = rl_hist_copy(i, history.history_buff);
	return (line);
}

char		*get_hist_expansions(char *line)
{
	char	*new_line;

	new_line = NULL;
	if (line && *line)
	{
		if ((line[0] == '-' && ft_isdigit(line[1]))
		|| ft_isdigit(line[0]))
			new_line = rl_digit_exp(ft_atoi(line), g_rl.history);
		else if (ft_strlen(line) == 1 && line[0] == '!')
			new_line = rl_digit_exp(-1, g_rl.history);
		else
			new_line = rl_search_exp(line, g_rl.history);
	}
	return (new_line);
}

size_t		get_hist_size(void)
{
	return (g_rl.history.hist_len);
}
