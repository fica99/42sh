/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:00:09 by filip             #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	set_sig_def(void);
void	synch_signal(int sig);
void	sigaction_set(void (*f)(int sig), struct sigaction *usr_action);
void	signalling(void);
void	signalling_chld(void);
void	sighandler_chld(int sign);
void	sighandler(int sign);
void	win_handler(int sign);

#endif
