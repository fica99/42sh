/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:53:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/13 22:08:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	redir_op(t_node *ast, t_term *term)
{
	int		fd;
	int		back_fd;
	int		new_fd;

	if (tk_type(ast->token, ERRED) || tk_type(ast->token, DERRED))
		new_fd = STDERR_FILENO;
	else if (tk_type(ast->token, RRED) || tk_type(ast->token, DRRED))
		new_fd = STDOUT_FILENO;
	else if (tk_type(ast->token, LRED) || tk_type(ast->token, DLRED))
		new_fd = STDIN_FILENO;
	else
	{
		amp_red(ast, term);
		return ;
	}
	if ((fd = get_expr_fd(ast)) == -1)
		return ;
	back_fd = copy_fd(fd, new_fd);
	exec_redir_command(ast, term);
	restore_fd(back_fd, new_fd);
}

void	exec_redir_command(t_node *ast, t_term *term)
{
	t_node *new_ast;

	new_ast = ast;
	while (new_ast->left && !tk_type(new_ast->left->token, EXPRESS) &&
	!tk_type(new_ast->left->token, PIPE))
		new_ast = new_ast->left;
	interpret_ast(new_ast->left, term);
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
			fd = open_tmp_heredoc_file(ast);
		else if (tk_type(ast->token, LRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, LRED_OPEN, 0);
		else if (tk_type(ast->token, RRED) || tk_type(ast->token, ERRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE);
		else if (tk_type(ast->token, DRRED) || tk_type(ast->token, DERRED))
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

int		open_tmp_heredoc_file(t_node *ast)
{
	int		fd;
	t_node	*expr;

	expr = ast->right;
	fd = open_red_file(HEREDOC_FILE,
	ast->token->type, RRED_OPEN, PERM_MODE);
	ft_putstr_fd(expr->token->lexeme, fd);
	close(fd);
	fd = open_red_file(HEREDOC_FILE,
	ast->token->type, O_RDONLY, PERM_MODE);
	return (fd);
}
