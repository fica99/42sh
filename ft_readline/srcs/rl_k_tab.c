/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:38:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/16 23:37:25 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char**	rl_autocom_env(short pos, t_readline *rl)
{
	char	*find;
	char	**res;

	if (rl->line.buffer[pos] == '(')
		++pos;
	if (!(find = ft_strsub(rl->line.buffer, pos, rl->cord.pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	res = get_env_dar(find, ALL_ENV);
	ft_strdel(&find);
	return (res);
}

void			rl_k_tab(t_readline *rl)
{
	short	pos;
	char	**res;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (ft_isspace(rl->line.buffer[rl->cord.pos]) ||
	!rl->line.buffer[rl->cord.pos])
		pos = rl->cord.pos;
	else
		pos = rl_prev_word(rl->line.buffer, rl->cord.pos);
	res = NULL;
	if (rl->line.buffer[pos] == '$')
		res = rl_autocom_env(pos, rl);
	// if (ft_darlen(res) > 1)
	// {
	// 	rl_autocom_print(res);
	// }
	// else
	// 	rl_autocom_add(res, rl);
	ft_free_dar(res);
}
