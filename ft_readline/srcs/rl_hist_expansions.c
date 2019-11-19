/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_hist_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:13:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/19 22:23:57 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*rl_update_line(short i, char *line)
{
	short	j;
	char	*new_line;

	new_line = rl_exp_to_line(index, g_rl.history.history_buff, line, j);
}

char	*rl_exp_to_line(short index, char **hist_buff, char *line, short i)
{
	short	j;
	char	*end;
	char	*new_line;

	j = i;
	while (line[j] && !ft_isspace(line[j]))
		++j;
	if (index < 0)
	{
		rl_print_err_exp(line, i, j);
		return (NULL);
	}
	end = NULL;
	if (line[j])
		if (!(end = ft_strdup(line + j)))
			rl_err("42sh", "malloc() error", UNDEFERR);
	if (!(new_line = ft_strnew(ft_strlen(line) + ft_strlen(hist_buff[index]))))
		rl_err("42sh", "malloc() error", UNDEFERR);
	line[i] = '\0';
	ft_strcat(ft_strcat(ft_strcat(new_line, line), hist_buff[index]), end);
	ft_strdel(&end);
	return (new_line);
}

void	rl_print_err_exp(char *line , int start_index, int end_index)
{
	ft_putstr("42sh: ");
	while (start_index != end_index)
		ft_putchar(line[start_index++]);
	ft_putendl(": event nont found");
}

void	rl_update_hist(char *line, t_rl_history *history)
{
	short	len;

	if ((len = history->hist_len - 1) >= 0)
	{
		ft_strdel(&history->history_buff[len]);
		if (line)
			if (!(history->history_buff[len] = ft_strdup(line)))
				rl_err("42sh", "malloc() error", ENOMEM);
	}
}
