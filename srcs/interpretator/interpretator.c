/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/19 21:50:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	interpret_ast(t_node *ast, t_term *term)
{
	if (!ast)
		return ;
	if (tk_type(ast->token, SEP))
	{
		interpret_ast(ast->left, term);
		interpret_ast(ast->right, term);
	}
	else if (tk_type(ast->token, PIPE))
		pipe_op(ast, term);
	else if (tk_type(ast->token, EXPRESS))
		make_command(ast->token->lexeme, term);
	else
		interpret_redir(ast, term);
}

void	interpret_redir(t_node *ast, t_term *term)
{
	if (tk_class(ast->token, C_RREDIR))
	{
		if (ast->left && tk_class(ast->left->token, C_RREDIR))
			interpret_ast(ast->left, term);
		rredir_op(ast, term);
	}
	else if (tk_class(ast->token, C_LREDIR))
	{
		if (ast->left && tk_class(ast->left->token, C_LREDIR))
			interpret_ast(ast->left, term);
		lredir_op(ast, term);
	}
	else if (tk_class(ast->token, C_CLOSE))
	{
		if (ast->left && tk_class(ast->left->token, C_CLOSE))
			interpret_ast(ast->left, term);
		aggr_fd_op(ast, term);
	}
}
