/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/09 18:03:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cord(void)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, &size) < 0)
	{
		print_error("minishell", "ioctl() error", NULL, 0);
		exit(-1);
	}
	cord.ws_col = size.ws_col;
}

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
	tty.c_lflag &= ~(ICANON | ECHO);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
	{
		print_error("minishell", "tcsetattr() error", NULL, EINVAL);//EBADF, ENOTTY, EINVAL
		exit(1);
	}
}

char	*ft_stradd(char	*buf, char s, size_t i)
{
	size_t	j;
	char 	*str;

	j = 0;
	str = NULL;
	while (buf[j] && j != i)
		j++;
	if (buf[j])
		str = &(buf[j]);
	else
		str = NULL;
	buf[j++] = s;
	while (str)
	{
		buf[j++] = *str;
		str++;
	}
	buf[j] = '\0';
	return (buf);
}
