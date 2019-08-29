/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/29 18:40:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*token_type(t_token *token, int type)
{
	if (!token)
		return (NULL);
	if (token->type == type)
		return (SOMETHING);
	return (NULL);
}

char		*token_class(t_token *token, int class)
{
	if (!token)
		return (NULL);
	if (token->class == class)
		return (SOMETHING);
	return (NULL);
}

void		*free_token(t_token **token)
{
	if (token && *token)
	{
		ft_memdel((void**)&((*token)->lexeme));
		ft_memdel((void**)token);
		*token = NULL;
	}
}

/*
###############################################################################
#                                                                             #
#  PARSER                                                                     #
#                                                                             #
###############################################################################
*/

t_node		*parser(char *str)
{
	t_node		*ast;
	t_token		*token;
	t_string	string;

	g_parser_flags = INIT_FLAGS;
	string.index = 0;
	string.str = str;
	ast = statement_list(&string);
	if (g_parser_flags & PARSER_ERROR)
	{
		free_ast(&ast);
		print_error_withoutexit("42sh", "Syntax error", NULL, NOERROR);
		return (NULL);
	}
	if (!token_type(token = get_next_token(str), EOL))
	{
		g_parser_flags |= PARSER_ERROR;
		print_error_withoutexit("42sh", "Syntax error", NULL, NOERROR);
		free_ast(&ast);
		ast = NULL;
		free_token(&token);
	}
	return (ast);
}

t_node		*statement_list(t_string *str)
{
	t_token	*token;
	t_node	*ast;
	short	copy;

	ast = NULL;
	while (LOOP)
	{
		token = NULL;
		if (!ast)
			ast = statement(str);
		if (g_parser_flags & PARSER_ERROR)
			break ;
		copy = str->index;
		if (token_type(token = get_next_token(str), ERROR))
		{
			g_parser_flags |= PARSER_ERROR;
			break ;
		}
		if (!token_type(token, SEP))
		{
			str->index = copy;
			break ;
		}
		ast = init_node(ast, token, statement(str));
	}
	free_token(&token);
	return (ast);
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
	short	copy;

	if (!(ast = pipe_ast(str)) || (g_parser_flags & PARSER_ERROR))
		return (ast);
	token = get_next_token(str);
	if (token_type(token, ERROR) || !token_class(token, REDIR))
	{
		if (token_type(token, ERROR))
			g_parser_flags |= PARSER_ERROR;
		else
			str->index = copy;
		free_token(&token);
		return (ast);
	}
	ast = init_node(ast, token, expr(str));
	if (!(ast->right))
		g_parser_flags |= PARSER_ERROR;
	return (ast);
}

t_node		*pipe_ast(t_string *str)
{
	t_node	*ast;
	t_node	*second;
	t_token	*token;
	short	copy;

	ast = NULL;
	while (LOOP)
	{
		if (!ast)
			ast = expr(str);
		if (!ast || (g_parser_flags & PARSER_ERROR))
			break ;
		copy = str->index;
		token = get_next_token(str);
		second = expr(str);
		if (token_type(token, ERROR) || !token_type(token, PIPE) || !second)
		{
			if (token_type(token, ERROR) || !second)
				g_parser_flags |= PARSER_ERROR;
			else
				str->index = copy;
			free_ast(&second);
			free_token(&token);
			break ;
		}
		ast = init_node(ast, token, expr(str));
	}
	return (ast);
}
