/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:53:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/07 18:05:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	redir_op(t_node *ast, t_term *term)
{
	int		fd;
	int		back_fd;
	int		new_fd;
	t_node	*new_ast;

	if (check_token_type(ast->token, ERRED) ||
	check_token_type(ast->token, DERRED))
		new_fd = STDERR_FILENO;
	else if (check_token_type(ast->token, RRED) ||
	check_token_type(ast->token, DRRED))
		new_fd = STDOUT_FILENO;
	else if (check_token_type(ast->token, LRED))
		new_fd = STDIN_FILENO;
	else
	{
		amp_red(ast, term);
		return ;
	}
	if ((fd = get_expr_fd(ast)) == -1)
		return ;
	back_fd = copy_fd(fd, new_fd);
	new_ast = exec_redir_command(ast, term);
	restore_fd(back_fd, new_fd);
	if (new_ast != ast)
		interpret_ast(ast->left, term);
}

t_node	*exec_redir_command(t_node *ast, t_term *term)
{
	t_node *new_ast;

	new_ast = ast;
	while (!check_token_type(new_ast->left->token, EXPRESS))
		new_ast = new_ast->left;
	interpret_ast(new_ast->left, term);
	return (new_ast);
}

int		get_expr_fd(t_node *ast)
{
	t_node	*expr;
	int		fd;

	expr = ast->right;
	fd = -1;
	if (check_token_type(expr->token, EXPRESS))
	{
		if (check_token_type(ast->token, LRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, LRED_OPEN, 0);
		if (check_token_type(ast->token, RRED) ||
		check_token_type(ast->token, ERRED))
			fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE);
		if (check_token_type(ast->token, DRRED) ||
		check_token_type(ast->token, DERRED))
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
			print_error_withoutexit("42sh", NULL, name, ENOENT);
			return (-1);
		}
		if (access(name, R_OK))
		{
			print_error_withoutexit("42sh", NULL, name, EACCES);
			return (-1);
		}
	}
	if ((fd = open(name, acc, mode)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	return (fd);
}
