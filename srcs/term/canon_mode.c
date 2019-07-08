/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canon_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:19:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/08 15:44:43 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		set_attr(struct termios *savetty)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, savetty) == -1)
		print_error("42sh", "tcsetattr() error", NULL, 0);
}

void		set_input_mode(struct termios *tty)
{
	save_attr(tty);
	tty->c_lflag &= ~(ICANON | ECHO | ISIG);
	tty->c_cc[VTIME] = 0;
	tty->c_cc[VMIN] = 1;
	set_attr(tty);
}

void		save_attr(struct termios *savetty)
{
	if (!isatty(0))
		print_error("42sh", "stdin not terminal\n", NULL, 0);
	if (tcgetattr(STDIN_FILENO, savetty) == -1)
		print_error("42sh", "tcgetattr() error", NULL, 0);
}
