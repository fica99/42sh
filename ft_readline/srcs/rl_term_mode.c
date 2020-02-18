/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_term_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:24:12 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/17 19:43:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_save_mode(struct termios *savetty)
{
	if (tcgetattr(STDIN_FILENO, savetty) == -1)
	{
		ft_putendl_fd("42sh: tcgetattr() error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void		rl_set_mode(struct termios *savetty)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, savetty) == -1)
	{
		ft_putendl_fd("42sh: tcssetattr() error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void		rl_set_non_canon_mode(struct termios *tty)
{
	rl_save_mode(tty);
	tty->c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
	tty->c_cc[VMIN] = 1;
	tty->c_cc[VTIME] = 0;
	rl_set_mode(tty);
}
