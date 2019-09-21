/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 21:45:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	interpret_ast(t_node *ast)
{
	if (!ast)
		return ;
	if (tk_type(ast->token, SEP))
	{
		interpret_ast(ast->left);
		interpret_ast(ast->right);
	}
	else if (tk_class(ast->token, C_RREDIR))
	{
		if (ast->left && tk_class(ast->left->token, C_RREDIR))
			interpret_ast(ast->left);
		rredir_op(ast);
	}
	else if (tk_class(ast->token, C_LREDIR))
	{
		if (ast->left && tk_class(ast->left->token, C_LREDIR))
			interpret_ast(ast->left);
		lredir_op(ast);
	}
	else if (tk_class(ast->token, C_CLOSE))
		closing_fd(ast);
	else if (tk_type(ast->token, PIPE))
		pipe_op(ast);
	else if (tk_type(ast->token, EXPRESS))
		make_command(ast->token->lexeme);
}
