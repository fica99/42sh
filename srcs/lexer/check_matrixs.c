/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_matrixs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:50:01 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

int			lx_define_union(t_token *token, t_token *next_token, t_lexer *lexer)
{
	t_matrix	*m_union;
	int			t_type;
	int			nt_type;

	if (!token || !next_token || !lexer)
		return (-2);
	t_type = token->type;
	nt_type = next_token->type;
	m_union = lexer->m_union;
	if (t_type < 0 || t_type >= m_union->rows)
		return (-2);
	if (nt_type < 0 || nt_type >= m_union->cols)
		return (-2);
	return (m_union->data[t_type][nt_type]);
}

int			lx_define_priority(t_token *token,
	t_token *next_token, t_lexer *lexer)
{
	t_matrix	*m_priority;
	int			t_type;
	int			nt_type;

	if (!token || !next_token || !lexer)
		return (-2);
	t_type = token->type;
	nt_type = next_token->type;
	m_priority = lexer->m_priority;
	if (t_type < 0 || t_type >= m_priority->rows)
		return (-2);
	if (nt_type < 0 || nt_type >= m_priority->cols)
		return (-2);
	return (m_priority->data[t_type][nt_type]);
}

int			lx_define_state(char symbol, int state, t_lexer *lexer)
{
	t_matrix	*m_type;

	m_type = lexer->m_type;
	if (symbol < 0 || symbol >= m_type->rows)
		return (-2);
	if (state < 0 || state >= m_type->cols)
		return (-2);
	return (m_type->data[(int)symbol][state]);
}
