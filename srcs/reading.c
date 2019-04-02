/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 12:50:45 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_input_mode (void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
}

void	set_input_mode(void)
{
	struct termios	tty;

	if (!isatty(0))
		print_error("minishell", "stdin not terminal\n", NULL, 0);
	if (tcgetattr(STDIN_FILENO, &savetty) < 0)
		print_error("minishell", "tcgetattr() error", NULL, 0);//EBADF, ENOTTY
	//Save the terminal attributes so we can restore them later
	 /*  Set the funny terminal modes. */
	tty = savetty;
	 tty.c_lflag &= ~(ICANON| ECHO); /*  Clear ICANON and ECHO. */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);// must check
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
		return (NULL);
	}
	while (RUNNING)
	{
		read(STDIN_FILENO, &c, 1);
		ft_putchar(c);
		if (c == '\n')
			break;
		buf[++i] = c;
	}
	if (i == -1)
		ft_memdel((void**)&buf);
	return (buf);
}