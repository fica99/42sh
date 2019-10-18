/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:35:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

t_node		*lredir_statement(t_node *ast, t_string *str)
{
	t_node	*right;
	t_token	*token;
	short	copy;

	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_class(token, C_LREDIR))
	{
		if (tk_type(token, FT_ERROR))
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
	return (lredir_statement(ast, str));
}

t_node		*pipe_statement(t_node *ast, t_string *str)
{
	t_token	*token;
	t_node	*right;
	short	copy;

	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_type(token, PIPE))
	{
		if (tk_type(token, FT_ERROR))
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
	return (pipe_statement(ast, str));
}

t_node		*rredir_statement(t_node *ast, t_string *str)
{
	t_node	*right;
	t_token	*token;
	short	copy;

	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_class(token, C_RREDIR))
	{
		if (tk_type(token, FT_ERROR))
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
	return (rredir_statement(ast, str));
}

t_node		*expr(t_string *str)
{
	t_token	*token;
	short	copy;
	t_node	*ast;

	copy = str->index;
	token = get_next_token(str, g_lexer);
	if (tk_type(token, FT_ERROR) || !tk_class(token, C_EXPRESS))
	{
		if (tk_type(token, FT_ERROR))
			g_parser_flags |= PARSER_ERROR;
		str->index = copy;
		free_token(&token);
		return (NULL);
	}
	if (!(ast = fd_aggr(str)))
		return (init_node(NULL, token, NULL));
	ast->left = init_node(NULL, token, NULL);
	return (ast);
}
