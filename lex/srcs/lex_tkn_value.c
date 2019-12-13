/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_tkn_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 22:05:57 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/12 22:15:01 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

int			lex_is_value(t_lex_tkn_type type)
{
	if (type == T_WORD || type == T_IO_NUMBER
		|| type == T_ASSIGNMENT_WORD || type == T_CONTROL_SUB)
		return (1);
	return (0);
}
