/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:22:46 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/14 19:38:35 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*get_token(t_string *str, t_lexer *lexer)
{
	t_lexer_params	prm;

	if (!str || !lexer)
		return (NULL);
	initial_lexer_params(&prm, str->index);
	while (1)
	{
		prm.type = (prm.state == -3) ? prm.type : prm.state;
		prm.state = next_state(str->str[prm.index], prm.type, lexer);
		if (prm.state > 0)
			if (!(add_symbol(&prm, str->str[prm.index])))
				return token_error();
		if (prm.state == -1)
			return (ready_token(str, prm));
		if (prm.state == -2)
			return token_error();
		if (str->str[prm.index])
			prm.index++;
	}
}

void		initial_lexer_params(t_lexer_params *prm, int start_index)
{
	prm->index = start_index;
	prm->state = 0;
	prm->type = 0;
	prm->s_index = 0;
	prm->str[LEXER_STR_LEN - 1] = '\0';
}

int			next_state(char symbol, int state, t_lexer *lexer)
{
	t_matrix	*m_type;

	m_type = lexer->m_type;
	if (symbol < 0 && symbol >= m_type->rows)
		return (-2);
	if (state < 0 && state >= m_type->cols)
		return (-2);
	return (m_type->data[(int)symbol][state]);
}

t_token		*new_token(void)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	token->lexeme = NULL;
	token->type = 0;
	token->class = 0;
	token->start_index = 0;
	token->fin_index = 0;
	return (token);
}

int			add_symbol(t_lexer_params *prm, char sym)
{
	if (prm->s_index + 1 >= LEXER_STR_LEN)
		return (0);
	prm->str[prm->s_index] = sym;
	prm->str[++(prm->s_index)] = '\0';
	return (1);
}