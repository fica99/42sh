/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/06 22:10:54 by ggrimes          ###   ########.fr       */
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
		print_error_withoutexit("42sh", "Syntax error", NULL, NOERROR);
		return (ast);
	}
	if (!check_token_type(token = get_next_token(&string, g_lexer), EOL))
	{
		g_parser_flags |= PARSER_ERROR;
		print_error_withoutexit("42sh", "Syntax error", NULL, NOERROR);
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
	if (check_token_type(token, FT_ERROR) ||
	!check_token_type(token, SEP))
	{
		if (check_token_type(token, FT_ERROR))
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
	t_token	*token;
	t_node	*end;
	short	copy;

	if (!(ast = pipe_ast(str)) || (g_parser_flags & PARSER_ERROR))
		return (ast);
	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (check_token_type(token, FT_ERROR) || !check_token_class(token, C_REDIR))
	{
		if (check_token_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (ast);
	}
	if (!(end = expr(str)))
		if (!(end = num_def(str)))
			g_parser_flags |= PARSER_ERROR;
	return (init_node(ast, token, end));
}

t_node		*pipe_ast(t_string *str)
{
	t_node	*ast;
	t_token	*token;
	short	copy;

	ast = expr(str);
	if (!ast || (g_parser_flags & PARSER_ERROR))
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
	return (init_node(ast, token, pipe_ast(str)));
}
