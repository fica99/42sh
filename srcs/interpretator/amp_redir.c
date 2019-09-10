/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:25:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/08 18:27:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	amp_red(t_node *ast, t_term *term)
{
	if (tk_type(ast->token, ARRED) || tk_type(ast->token, ADRRED)
	|| tk_type(ast->token, DRREDA) || tk_type(ast->token, RREDA))
		amprred_op(ast, term);
}

void	amprred_op(t_node *ast, t_term *term)
{
	int		back_fd;
	int		fd;
	int		back_fd_two;
	t_node	*new_ast;
	t_node	*expr;

	expr = ast->right;
	if (tk_type(expr->token, EXPRESS))
	{
		if (tk_type(ast->token, ARRED) || tk_type(ast->token, RREDA))
			if ((fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE)) == -1)
				return ;
		if (tk_type(ast->token, ADRRED) || tk_type(ast->token, DRREDA))
			if ((fd = open_red_file(expr->token->lexeme,
			ast->token->type, DRRED_OPEN, PERM_MODE)) == -1)
				return ;
		back_fd = copy_fd(fd, STDOUT_FILENO);
		back_fd_two = copy_fd(fd, STDERR_FILENO);
		new_ast = exec_redir_command(ast, term);
		restore_fd(back_fd, STDOUT_FILENO);
		restore_fd(back_fd_two, STDERR_FILENO);
		if (new_ast != ast)
			interpret_ast(ast->left, term);
	}
}
