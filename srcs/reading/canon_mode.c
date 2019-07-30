/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canon_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:19:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/31 01:14:59 by aashara-         ###   ########.fr       */
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
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("42sh: isatty() error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, savetty) == -1)
	{
		ft_putstr_fd("42sh: tcgetattr() error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
