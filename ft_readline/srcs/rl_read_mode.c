/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_read_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:00:56 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/24 16:42:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void		rl_save_attr(struct termios *savetty)
{
	if (tcgetattr(STDIN_FILENO, savetty) == -1)
	{
		ft_putendl_fd("42sh: tcgetattr() error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void		rl_set_non_canon_mode(struct termios *tty)
{
	rl_save_attr(tty);
	tty->c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
	tty->c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	tty->c_cflag |= (CS8);
	tty->c_cc[VMIN] = 0;
	tty->c_cc[VTIME] = 1;
	rl_set_attr(tty);
}

void		rl_set_attr(struct termios *savetty)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, savetty) == -1)
		rl_err("42sh", "tcsetattr() error", UNDEFERR);
}
