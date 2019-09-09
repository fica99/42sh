/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/09 19:50:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	interpret_ast(t_node *ast, t_term *term)
{
	if (ast)
	{
		if (tk_type(ast->token, SEP))
		{
			interpret_ast(ast->left, term);
			interpret_ast(ast->right, term);
		}
		if (tk_type(ast->token, PIPE))
			pipe_op(ast, term);
		if (tk_class(ast->token, C_REDIR))
			redir_op(ast, term);
		if (tk_type(ast->token, EXPRESS))
			make_command(ast->token->lexeme, term);
		if (tk_class(ast->token, C_CLOSE))
			closing_fd(ast, term);
	}
}
