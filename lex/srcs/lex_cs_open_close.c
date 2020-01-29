/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cs_open_close.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:38:12 by ggrimes           #+#    #+#             */
/*   Updated: 2020/01/29 22:25:02 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int	lex_cs_is_quotes(t_lex_cs_type type)
{
	if (type >= CS_DOUBLE_QUOTES && type <= CS_BACK_QUOTES)
		return (1);
	return (0);
}

int	lex_cs_is_brk(t_lex_cs_type type)
{
	if (type >= CS_ROUND_BRK && type <= CS_D_ROUND_BRK)
		return (1);
	return (0);
}

int	lex_cs_check_open(int check, t_lex_cs_type *cs_filter,
	int cs_count, t_lex_cs_type type)
{
	if (!cs_filter)
		return (0);
	if (check == 1)
		return (1);
	if ((cs_count == -1 && check == 2) || (cs_count != -1
		&& check == 2 && cs_filter[cs_count] != type))
		return (1);
	return (0);
}

int	lex_cs_check_close(int check, t_lex_cs_type *cs_filter,
	int cs_count, t_lex_cs_type type)
{
	if (!cs_filter)
		return (0);
	if (cs_count == -1)
		return (0);
	if (check != 0 && cs_filter[cs_count] == type)
		return (1);
	return (0);
}
