/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:22:46 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

t_token		*lx_get_token(t_string *str, t_lexer *lexer)
{
	t_lexer_params	prm;

	if (!str || !lexer)
		return (NULL);
	initial_lexer_params(&prm, str->index);
	while (1)
	{
		prm.type = (prm.state == -3) ? prm.type : prm.state;
		if ((prm.state = lx_define_state(str->str[prm.index],
			prm.type, lexer)) == -2)
			return (lx_token_error("State definition", str));
		if (prm.state > 0)
			if (!(add_symbol(&prm, str->str[prm.index])))
				return (lx_token_error("Excess LEXER_STR_LEN", str));
		if (prm.state == -1)
			return (lx_ready_token(str, prm, lexer));
		if (prm.state == -2)
			return (lx_token_error("Grammar", str));
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
