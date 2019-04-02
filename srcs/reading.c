/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 20:38:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_input_mode (void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &savetty) < 0)
	{
		print_error("minishell", "tcsetattr() error", NULL, EINVAL);//EBADF, ENOTTY, EINVAL
		exit(1);
	}
}

void	set_input_mode(void)
{
	struct termios	tty;

	if (!isatty(0))
	{
		print_error("minishell", "stdin not terminal\n", NULL, 0);
		exit(1);
	}
	if (tcgetattr(STDIN_FILENO, &savetty) < 0)
	{
		print_error("minishell", "tcgetattr() error", NULL, ENOTTY);//EBADF, ENOTTY
		exit(1);
	}
	tty = savetty;
	 tty.c_lflag &= ~(ICANON| ECHO| ECHOE); /*  Clear ICANON and ECHO. */
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
	{
		print_error("minishell", "tcsetattr() error", NULL, EINVAL);//EBADF, ENOTTY, EINVAL
		exit(1);
	}
}

char	*read_prompt(void)
{
	char	*buf;
	char	c;
	short	i;

	set_input_mode();
	i = -1;
	if (!(buf = ft_strnew(LINE_MAX)))
	{
		print_error("minishell", "malloc() error", NULL, ENOMEM);
		exit(1);
	}
	while (RUNNING && i < LINE_MAX)
	{
		read(STDIN_FILENO, &c, 1);
		ft_putchar(c);
		if (c == '\n')
			break;
		buf[++i] = c;
	}
	if (i == -1 || i >= LINE_MAX)
		ft_memdel((void**)&buf);
	return (buf);
}