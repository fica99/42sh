/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/08 18:24:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>

# define LRED_OPEN O_RDONLY
# define RRED_OPEN O_WRONLY | O_CREAT | O_TRUNC
# define DRRED_OPEN O_WRONLY | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

/*
**	interpretator.c
*/
void	interpret_ast(t_node *ast, t_term *term);
/*
**	pipes.c
*/
void	pipe_op(t_node *ast, t_term *term);
void	left_child(int *pid, int *pipes, t_node *expr, t_term *term);
void	right_child(int *pid, int *pipes, t_node *expr, t_term *term);
/*
**	redir.c
*/
void	redir_op(t_node *ast, t_term *term);
t_node	*exec_redir_command(t_node *ast, t_term *term);
int		get_expr_fd(t_node *ast);
int		open_red_file(char *name, token_type red_type, int acc, int mode);
/*
**	dup_fd.c
*/
int		copy_fd(int fd, int new_fd);
void	restore_fd(int back_fd, int new_fd);
/*
**	amp_redir.c
*/
void	amp_red(t_node *ast, t_term *term);
void	amprred_op(t_node *ast, t_term *term);
/*
**	closing_fd.c
*/


#endif
