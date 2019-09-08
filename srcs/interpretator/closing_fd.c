/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:21:55 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/08 19:13:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

// void	closing_fd(t_node *ast, t_term *term)
// {
// 	int		fd;

// 	if (tk_type(ast->token, CLOUT))
// 	{

// 	}
// }



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
