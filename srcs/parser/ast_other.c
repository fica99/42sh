/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:35:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/07 18:23:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*pipe_statement(t_string *str)
{
	t_node	*ast;
	t_token	*token;
	short	copy;

	if (!(ast = expr(str)))
		return (ast);
	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (check_token_type(token, FT_ERROR) ||
	!check_token_type(token, PIPE))
	{
		if (check_token_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (ast);
	}
	return (init_node(ast, token, pipe_statement(str)));
}

t_node		*expr(t_string *str)
{
	t_token	*token;
	short	copy;

	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (check_token_type(token, FT_ERROR) || !check_token_class(token, C_EXPRESS))
	{
		if (check_token_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (NULL);
	}
	return (init_node(NULL, token, NULL));
}
