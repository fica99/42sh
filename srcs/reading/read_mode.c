/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:19:06 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 20:27:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void		set_attr(struct termios *savetty)
{
	if (!(savetty->c_iflag) && !(savetty->c_oflag) && !(savetty->c_cflag)
	&& !(savetty->c_lflag) && !(savetty->c_ispeed) && !(savetty->c_ospeed)
	&& !*(savetty->c_cc))
		return ;
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
	{
		ft_putstr_fd("tcgetattr() error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	init_terminfo(void)
{
	int		err;

	if (!isatty(STDIN_FILENO))
		err_exit(g_argv[0], "stdin is not a terminal", NULL, NULL);
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
