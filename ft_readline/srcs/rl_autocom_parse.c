/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_autocom_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 20:35:26 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/21 19:30:41 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char		rl_autocom_is_bin(char *buff, short pos)
{
	if (buff[pos] == '|' || buff[pos] == ';')
		return (TRUE);
	while (--pos >= 0)
		if (!ft_isspace(buff[pos]))
			return (FALSE);
	return (TRUE);
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
		if (ft_isspace(rl->line.buffer[pos]) || rl->line.buffer[pos] == '|'
				|| rl->line.buffer[pos] == ';')
		{
			if (rl_autocom_is_bin(rl->line.buffer, pos))
				break ;
			autocom->is_path = TRUE;
			return (pos + 1);
		}
	}
	autocom->is_bin = TRUE;
	return (pos + 1);
}

void			rl_autocom_parse(t_rl_autocom_parse *autocom, t_readline *rl)
{
	autocom->res = NULL;
	autocom->to_find = NULL;
	autocom->is_bin = FALSE;
	autocom->is_path = FALSE;
	autocom->is_env = FALSE;
	autocom->pos = rl_autocom_find_pos(autocom, rl);
	if (!rl->line.buffer[autocom->pos] || autocom->pos == rl->cord.pos)
	{
		if (!(autocom->to_find = ft_strnew(1)))
			rl_err("42sh", "malloc() error", ENOMEM);
	}
	else
	{
		if (!(autocom->to_find = ft_strsub(rl->line.buffer, autocom->pos,
												rl->cord.pos - autocom->pos)))
			rl_err("42sh", "malloc() error", ENOMEM);
	}
}
