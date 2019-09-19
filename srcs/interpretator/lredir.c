/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lredir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:25:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/19 21:30:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	lredir_op(t_node *ast, t_term *term)
{
	int		new_fd;
	int		fd;
	int		back_fd;

	if (tk_type(ast->token, LRED) || tk_type(ast->token, DLRED))
		new_fd = STDIN_FILENO;
	else
		return ;
	if ((fd = get_expr_fd(ast)) == -1)
		return ;
	back_fd = copy_fd(fd, new_fd);
	exec_redir_command(ast, term, C_LREDIR);
	restore_fd(back_fd, new_fd);
}
