/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:53:51 by filip             #+#    #+#             */
/*   Updated: 2019/04/27 23:54:28 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef COMMAND_H
# define COMMAND_H

# define RIGHT "\033[C"
# define LEFT "\033[D"
# define SAVE_CUR(fd) ft_putstr_fd("\0337", fd)
# define RESTORE_CUR(fd) ft_putstr_fd("\0338", fd)
# define CLEAN_SCREEN(fd) ft_putstr_fd("\033[0J", fd)
# define HOME "\033[H"
# define END "\033[F"
# define CTRL_UP "\033[1;5A"
# define CTRL_DOWN "\033[1;5B"
# define CTRL_RIGHT "\033[1;5C"
# define CTRL_LEFT "\033[1;5D"
# define PREV_LINE "\033[F"
# define NEXT_LINE "\033[E"
# define BCSP 127
# define CTRL_H 8
# define CTRL_D 4
# define CTRL_C 3
# define TAB 9
# define DEL "\033[3~"
# define CUR_CORD "\033[6n"

#endif