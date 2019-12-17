/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkn_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:35:39 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/17 22:42:27 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_lex_tkn_class		lex_check_class(t_lex_tkn_type type)
{
	if (type == T_WORD)
		return (C_WORD);
	else if (type == T_ASSIGNMENT_WORD)
		return (C_ASSIGNMENT_WORD);
	else if (type == T_PIPE)
		return (C_PIPE);
	else if (type >= T_GREATER && type <= T_IO_NUMBER)
		return (C_REDIR);
	else if (type == T_SEP)
		return (C_SEP);
	else if (type == T_CONTROL_SUB)
		return (C_CONTROL_SUB);
	else if (type == T_END)
		return (C_END);
	else
		return (C_NULL);
}
