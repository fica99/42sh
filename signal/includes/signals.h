/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:00:09 by filip             #+#    #+#             */
/*   Updated: 2019/09/09 22:42:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

//# include <signals.h>

/*
**	signal.c
*/

void	synch_signal(int sig);
void	sigaction_set(void (*f)(int sig), struct sigaction *usr_action);
void	signalling(void);
void	signalling_chld(void);
void 	sighandler_chld(int sign);
void    sighandler(int sign);
void	win_handler(int sign);
#endif
