/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/30 22:39:06 by aashara-         ###   ########.fr       */
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
     tcgetattr(STDIN_FILENO, &tty);
	 tty.c_lflag &= ~(ICANON|ECHO); /*  Clear ICANON and ECHO. */
	 tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}

char	*read_prompt(void)
{
	char	buf[PROMPT_LEN + 1];
	char	*arr;
	char	*arr1;

	arr = NULL;
	set_input_mode();
	while (RUNNING)
	{
		read(STDIN_FILENO, &buf, PROMPT_LEN);
		buf[PROMPT_LEN] = '\0';
		ft_putstr(buf);
		if (!arr)
		{
			if (!(arr = ft_strdup(buf)))
				print_error("minishell", "malloc() error", NULL, ENOMEM);
		}
		else
		{
			if (!(arr1 = ft_strjoin(arr, buf)))
				print_error("minishell", "malloc() error", NULL, ENOMEM);
			ft_memdel((void**)&arr);
			arr = arr1;
		}
		if ((arr1 = check_new_line(arr)) != NULL)
			break;
	}
	reset_input_mode();
	return (arr1);
}