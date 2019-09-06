/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:25:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/06 21:55:46 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	amp_red(t_node *ast, t_term *term)
{
	int	fd;

	if (check_token_type(ast->token, ARRED))
		amprred_op(ast, term);
}

void	amprred_op(t_node *ast, t_term *term)
{
	int		back_fd;
	int		fd;
	int		back_fd_two;
	t_node	*expr;

	expr = ast->right;
	if (check_token_type(ast->token, ARRED))
	{
		if (check_token_type(expr->token, EXPRESS))
		{
			if ((fd = open_red_file(expr->token->lexeme,
			ast->token->type, RRED_OPEN, PERM_MODE)) == -1)
				return ;
		}
		else
			return ;
		back_fd = copy_fd(fd, STDOUT_FILENO);
		back_fd_two = copy_fd(fd, STDERR_FILENO);
		interpret_ast(ast->left, term);
		restore_fd(back_fd, STDOUT_FILENO);
		restore_fd(back_fd_two, STDERR_FILENO);
	}
}


// int		get_fd(t_node *ast)
// {
// 	int		fd;
// 	t_node	*aggr;

// 	aggr = ast->right;
// 	fd = get_expr_fd(ast);
// 	if (check_token_type(ast->token, RARED) ||
// 	check_token_type(ast->token, LARED))
// 	{
// 		if (check_token_type(aggr->token, DEF))
// 			if (!(fd = open("/dev/null", 0)))
// 				print_error("42sh", "open() error", "/dev/null", 0);
// 		if (check_token_type(aggr->token, NUM))
// 		{
// 			fd = ft_atoi(aggr->token->lexeme);
// 			if (fd < 0 || fd >= 3)
// 			{
// 				print_error_withoutexit("42sh", "Syntax error", NULL, EBADF);
// 				return (-1);
// 			}
// 		}
// 	}
// 	return (fd);
// }
