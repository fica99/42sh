/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:19:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/22 15:34:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		set_attr(struct termios *savetty)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, savetty) == -1)
		err_exit(g_argv[0], "tcsetattr() error", NULL, NOERROR);
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
	if (tcgetattr(STDIN_FILENO, savetty) == -1)
		err_exit(g_argv[0], "tcgetattr() error", NULL, NULL);
}

void		is_stdin_term(void)
{
	if (!isatty (STDIN_FILENO))
		err_exit(g_argv[0], "stdin is not a terminal", NULL, NULL);
}

void	init_terminfo(void)
{
	int		err;

	is_stdin_term();
	if ((setupterm(0, STDIN_FILENO, &err) == ERR))
	{
		if (err == 1)
			err_exit(g_argv[0], "setupterm() error", EHRDCPY, NOERROR);
		else if (err == 0)
			err_exit(g_argv[0], "setupterm() error", ENTFND, NOERROR);
		else if (err == -1)
			err_exit(g_argv[0], "setupterm() error", ENOTERMINFO, NOERROR);
	}
}
