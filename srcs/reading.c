/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/01 17:04:46 by aashara-         ###   ########.fr       */
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
	char	buf;
	char	*arr;
	ushort	nb;
	ushort	i;

	set_input_mode();
	i = 0;
	arr = ft_strnew(LINE_MAX + 1);
	while (RUNNING)
	{
		nb = read(STDIN_FILENO, &buf, 1);
		ft_putchar(buf);
		if (buf == '\n' || ft_strlen(arr) != 0)
			break;
		arr[i++] = buf;
	}
	reset_input_mode();
	return (arr);
}