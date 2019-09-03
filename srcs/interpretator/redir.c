/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:53:29 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/03 18:57:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	redir_op(t_node *ast, t_term *term)
{
	int		fd;
	int		back_fd;
	int		new_fd;

	if (!(fd = get_red_fd(ast)))
			return ;
	new_fd = STDOUT_FILENO;
	if (check_token_type(ast->token, LRED))
		new_fd = STDIN_FILENO;
	if ((back_fd = dup(new_fd)) == -1)
		print_error("42sh", "dup() error", NULL, NOERROR);
	if (dup2(fd, new_fd) == -1)
		print_error("42sh", "dup2() error", NULL, NOERROR);
	close(fd);
	interpret_ast(ast->left, term);
	if (dup2(back_fd, new_fd) == -1)
		print_error("42sh", "dup2() error", NULL, NOERROR);
}

int		get_red_fd(t_node *ast)
{
	t_node	*expr;
	int		fd;

	expr = ast->right;
	if (check_token_type(ast->token, LRED))
		if (!(fd = open_red_file(expr->token->lexeme, ast->token->type
		, LRED_OPEN, 0)))
			return (0);
	if (check_token_type(ast->token, RRED))
		if (!(fd = open_red_file(expr->token->lexeme, ast->token->type
		, RRED_OPEN, PERM_MODE)))
			return (0);
	if (check_token_type(ast->token, DRRED))
		if (!(fd = open_red_file(expr->token->lexeme, ast->token->type
		, DRRED_OPEN, PERM_MODE)))
			return (0);
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
