/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/30 20:34:29 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>

# define LRED_OPEN O_RDONLY
# define RRED_OPEN O_WRONLY | O_CREAT | O_TRUNC
# define DRRED_OPEN O_WRONLY | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

void	interpret_ast(t_node *ast, t_term *term);
void	pipe_op(t_node *ast, t_term *term);
void	redir_op(t_node *ast, t_term *term);
int		fd_red_file(char *name, int red_type, int acc, int mode);
#endif
