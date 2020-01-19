/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 21:38:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/19 18:07:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void		rl_autocom_env_params(t_rl_autocom_parse *autocom,
													t_readline *rl)
{
	if (!rl->line.buffer[autocom->pos] || autocom->pos == rl->cord.pos)
	{
		if (!(autocom->to_find = ft_strnew(1)))
			rl_err("42sh", "malloc() error", UNDEFERR);
	}
	else
	{
		if (!(autocom->to_find = ft_strsub(rl->line.buffer, autocom->pos ,
												rl->cord.pos - autocom->pos)))
			rl_err("42sh", "malloc() error", UNDEFERR);
	}
	autocom->res = get_env_names_dar(autocom->to_find, ALL_ENV);
}

static short	rl_autocom_find_pos(t_rl_autocom_parse *autocom,
															t_readline *rl)
{
	short	pos;

	pos = rl->cord.pos;
	while (--pos >= 0)
	{
		if (rl->line.buffer[pos] == '$' && (!pos ||
						!ft_isalnum(rl->line.buffer[pos - 1])))
		{
			autocom->is_env = TRUE;
			return (pos + 1);
		}
	}
	if (pos == -1)
		autocom->is_bin = TRUE;
	return (0);
}

static void		rl_autocom_parse(t_rl_autocom_parse *autocom, t_readline *rl)
{
	autocom->res = NULL;
	autocom->to_find = NULL;
	autocom->is_bin = FALSE;
	autocom->is_path = FALSE;
	autocom->is_env = FALSE;
	autocom->pos = rl_autocom_find_pos(autocom, rl);
	if (autocom->is_env == TRUE)
		rl_autocom_env_params(autocom, rl);
}

void			rl_k_tab(t_readline *rl)
{
	t_rl_autocom_parse	autocom;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_autocom_parse(&autocom, rl);
	rl_autocom_print(&autocom, rl);
	ft_strdel(&autocom.to_find);
	ft_free_dar(autocom.res);
}
