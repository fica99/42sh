/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/02 12:32:30 by filip            ###   ########.fr       */
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
		print_error("minishell", "stdin not terminal\n", NULL, 0); //EBADF, ENOTTY
	tcgetattr(STDIN_FILENO, &savetty);//Save the terminal attributes so we can restore them later
	 /*  Set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tty);// must check for err
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
	buf = ft_strnew(LINE_MAX);
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