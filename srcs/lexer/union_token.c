/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:20:10 by ggrimes           #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

t_token		*lx_get_union_token(t_lexer *lexer, t_string *str)
{
	t_token	*token;
	t_token	*next_token;
	int		class;

	token = (t_token *)ft_fifo(1, "get", NULL);
	while ((next_token = (t_token *)ft_fifo(1, "get", NULL)))
		if (!(token = lx_join_token(token, next_token)))
			return (NULL);
	if (!(token->lexeme = lx_del_spaces(token->lexeme)))
		return (NULL);
	if ((token->type = lx_generalization_type(token->type,
		lexer->m_generalization)) == -2)
	{
		lx_clear_token(&token);
		return (lx_token_error("Error: define generalization", str));
	}
	if ((class = lx_define_class(token->type, lexer->m_class)) == -2)
		return (lx_class_error(token, next_token, "class definition", str));
	token->class = class;
	return (token);
}

char		*lx_del_spaces(char *lexeme)
{
	char	*tmp;

	if (!(tmp = ft_strtrim(lexeme)))
		return (NULL);
	free(lexeme);
	return (tmp);
}

t_token		*lx_join_token(t_token *token, t_token *next_token)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(token->lexeme, next_token->lexeme)))
		return (NULL);
	free(token->lexeme);
	token->lexeme = tmp;
	lx_clear_token(&next_token);
	return (token);
}

int			lx_generalization_type(int type, t_matrix *m_generalization)
{
	if (!m_generalization)
		return (-2);
	if (type < 0 || type >= m_generalization->cols)
		return (-2);
	return (m_generalization->data[0][type]);
}
