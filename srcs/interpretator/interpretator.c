/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/01 18:50:15 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	interpret_ast(t_node *ast, t_term *term)
{
	if (ast)
	{
		if (check_token_type(ast->token, SEP))
		{
			interpret_ast(ast->left, term);
			interpret_ast(ast->right, term);
		}
		if (check_token_type(ast->token, PIPE))
			pipe_op(ast, term);
		if (check_token_class(ast->token, C_REDIR))
			redir_op(ast, term);
		if (check_token_type(ast->token, EXPRESS))
			make_command(ast->token->lexeme, term);
	}
}

void	redir_op(t_node *ast, t_term *term)
{
	int		fd;
	t_node	*expr;

	expr = ast->right;
	if (check_token_type(ast, LRED))
		if (!(fd = fd_red_file(expr->token->lexeme, expr->token->type
		, LRED_OPEN, 0)))
			return ;
	if (check_token_type(ast, RRED))
		if (!(fd = fd_red_file(expr->token->lexeme, expr->token->type
		, RRED_OPEN, PERM_MODE)))
			return ;
	if (check_token_type(ast, DRRED))
		if (!(fd = fd_red_file(expr->token->lexeme, expr->token->type
		, DRRED_OPEN, PERM_MODE)))
			return ;
	if (check_token_type(ast, DRRED) || check_token_type(ast, LRED))
		if (dup2(fd, STDOUT_FILENO) == -1)
			print_error("42sh", "dup2() error", NULL, NOERROR);
	if (check_token_type(ast, LRED))
		if (dup2(fd, STDIN_FILENO) == -1)
			print_error("42sh", "dup2() error", NULL, NOERROR);
	interpret_ast(ast->left, term);
	close(fd);
}

void	pipe_op(t_node *ast, t_term *term)
{
	int	pipes[2];
	int	pid[2];

	if (pipe(pipes) != 0)
		print_error("42sh", "pipe() error", NULL, NOERROR);
	if ((pid[0] = make_process()) == 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			print_error("42sh", "dup2() error", NULL, NOERROR);
		close(pipes[0]);
		interpret_ast(ast->left, term);
		exit(0);
	}
	if ((pid[1] = make_process()) == 0)
	{
		if (dup2(pipes[0], STDOUT_FILENO) == -1)
			print_error("42sh", "dup2() error", NULL, NOERROR);
		close(pipes[1]);
		interpret_ast(ast->right, term);
		exit(0);
	}
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
}

int		fd_red_file(char *name, int red_type, int acc, int mode)
{
	int	fd;

	if (red_type == LRED)
	{
		if (access(name, F_OK))
		{
			print_error_withoutexit("42sh", NULL, name, ENOENT);
			return (0);
		}
		if (access(name, R_OK))
		{
			print_error_withoutexit("42sh", NULL, name, EACCES);
			return (0);
		}
	}
	if ((fd = open(name, acc, mode)) == -1)
		print_error("42sh", "open() error", NULL, 0);
	return (fd);
}
