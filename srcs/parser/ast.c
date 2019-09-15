/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/15 14:46:31 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_node		*parser(char *str)
{
	t_node		*ast;
	t_token		*token;
	t_string	string;

	if (!str)
		return (NULL);
	g_parser_flags = INIT_FLAGS;
	string.index = 0;
	string.str = str;
	print_token(&string);
	return (NULL);
	ast = statement_list(&string);
	if (g_parser_flags & PARSER_ERROR)
	{
		err("42sh", "Syntax error", NULL, NOERROR);
		return (ast);
	}
	if (!tk_type(token = get_next_token(&string, g_lexer), EOL))
	{
		g_parser_flags |= PARSER_ERROR;
		err("42sh", "Syntax error", NULL, NOERROR);
	}
	free_token(&token);
	return (ast);
}

t_node		*statement_list(t_string *str)
{
	t_token	*token;
	t_node	*ast;
	short	copy;

	ast = statement(str);
	if (g_parser_flags & PARSER_ERROR)
		return (ast);
	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_class(token, C_SEP))
	{
		if (tk_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (ast);
	}
	return (init_node(ast, token, statement_list(str)));
}

t_node		*statement(t_string *str)
{
	t_node	*ast;

	ast = thread_statement(str);
	return (ast);
}

t_node		*thread_statement(t_string *str)
{
	t_node	*ast;
	short	copy;
	t_token	*token;

	if (!(ast = expr(str)))
		return (ast);
	if (!(ast = lredir_statement(ast, str)) || (g_parser_flags & PARSER_ERROR))
		return (ast);
	if (!(ast = pipe_statement(ast, str)) || (g_parser_flags & PARSER_ERROR))
		return (ast);
	if (!(ast = rredir_statement(ast, str)) || (g_parser_flags & PARSER_ERROR))
		return (ast);
	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_class(token, C_CLOSE))
	{
		if (tk_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (ast);
	}
	return (init_node(ast, token, NULL));
}
