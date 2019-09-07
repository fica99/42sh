/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/07 18:21:22 by aashara-         ###   ########.fr       */
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
	//print_token(&string);
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
	if (check_token_type(token, FT_ERROR) || !check_token_class(token, C_SEP))
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

	ast = pipe_statement(str);
	if (!ast || (g_parser_flags & PARSER_ERROR))
		return (ast);
	return (redir_statement(ast, str));
}

t_node		*redir_statement(t_node *ast, t_string *str)
{
	t_node	*right;
	t_token	*token;
	short	copy;

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
	if (!(right = expr(str)))
	{
		free_token(&token);
		return (ast);
	}
	ast = init_node(ast, token, right);
	return (redir_statement(ast, str));
}
