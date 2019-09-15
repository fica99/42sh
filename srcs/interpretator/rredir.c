/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rredir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:53:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/15 19:29:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	rredir_op(t_node *ast, t_term *term)
{
	int		fd;
	int		back_fd;
	int		new_fd;

	if (tk_type(ast->token, ERRED) || tk_type(ast->token, EDRRED))
		new_fd = STDERR_FILENO;
	else if (tk_type(ast->token, RRED) || tk_type(ast->token, DRRED))
		new_fd = STDOUT_FILENO;
	else if (tk_type(ast->token, ARRED) || tk_type(ast->token, ADRRED))
	{
		amprred_op(ast, term);
		return ;
	}
	else
		return ;
	if ((fd = get_expr_fd(ast)) == -1)
		return ;
	back_fd = copy_fd(fd, new_fd);
	exec_redir_command(ast, term, C_RREDIR);
	restore_fd(back_fd, new_fd);
}

void	amprred_op(t_node *ast, t_term *term)
{
	int		back_fd;
	int		fd;
	int		back_fd_two;
	t_node	*expr;

	expr = ast->right;
	if (tk_type(expr->token, EXPRESS))
	{
		if (tk_type(ast->token, ARRED))
			if ((fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE)) == -1)
				return ;
		if (tk_type(ast->token, ADRRED))
			if ((fd = open_red_file(expr->token->lexeme,
			ast->token->type, DRRED_OPEN, PERM_MODE)) == -1)
				return ;
		back_fd = copy_fd(fd, STDOUT_FILENO);
		back_fd_two = copy_fd(fd, STDERR_FILENO);
		exec_redir_command(ast, term, C_RREDIR);
		restore_fd(back_fd, STDOUT_FILENO);
		restore_fd(back_fd_two, STDERR_FILENO);
	}
}


int		get_expr_fd(t_node *ast)
{
	t_node	*expr;
	int		fd;

	expr = ast->right;
	fd = -1;
	if (tk_type(expr->token, EXPRESS))
	{
		if (tk_type(ast->token, DLRED))
			fd = open_red_file(HEREDOC_FILE,
			ast->token->type, O_RDONLY, PERM_MODE);
		else if (tk_type(ast->token, LRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, LRED_OPEN, 0);
		else if (tk_type(ast->token, RRED) || tk_type(ast->token, ERRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE);
		else if (tk_type(ast->token, DRRED) || tk_type(ast->token, EDRRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, DRRED_OPEN, PERM_MODE);
	}
	return (fd);
}

int		open_red_file(char *name, token_type red_type, int acc, int mode)
{
	int	fd;

	if (red_type == LRED)
	{
		if (access(name, F_OK))
		{
			err("42sh", NULL, name, ENOENT);
			return (-1);
		}
		if (access(name, R_OK))
		{
			err("42sh", NULL, name, EACCES);
			return (-1);
		}
	}
	if ((fd = open(name, acc, mode)) == -1)
		err_exit("42sh", "open() error", NULL, NOERROR);
	return (fd);
}

void	exec_redir_command(t_node *ast, t_term *term, token_class class)
{
	t_node *new_ast;

	new_ast = ast;
	while (new_ast->left && tk_class(new_ast->left->token, class))
		new_ast = new_ast->left;
	interpret_ast(new_ast->left, term);
}
