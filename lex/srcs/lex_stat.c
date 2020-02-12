/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:02:14 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/12 20:35:38 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn	*lex_status(t_lex_tkn_type type, t_lex_tkn *token)
{
	if (type == T_ERR)
		g_lex_stat = LS_ERR;
	else if (type == T_CTRL_C)
		g_lex_stat = LS_CTRL_C;
	else if (type == T_CTRL_D)
		g_lex_stat = LS_CTRL_D;
	else
		g_lex_stat = LS_OK;
	if (g_lex_stat == LS_OK)
		return (token);
	return (NULL);
}
