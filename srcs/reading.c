/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/05 17:47:33 by aashara-         ###   ########.fr       */
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

t_tc	*init_termcap(t_tc *tc)
{
	int 	success;

	if (!ft_getenv("TERM"))
	{
		print_error("minishell", "terminal type is not defined", NULL, 0);
		exit(1);
	}
	success = tgetent(NULL, ft_getenv("TERM"));
	if (success < 0)
	{
		print_error("minishell", "terminal type is not defined", NULL, 0);
		exit(1);
	}
	if (!success)
	{
		print_error("minishell", "could not access to termcap database", NULL, 0);
		exit(1);
	}
	tc->up = tgetstr("up", NULL);
	tc->down = tgetstr("do", NULL);
	tc->left = tgetstr("le", NULL);
	tc->right = tgetstr("ri", NULL);
	tc->bcsp = tgetstr("kbs", NULL);
	return (tc);
}

char	*reading(t_tc *tc, char *buf)
{
	char	c;
	int		i;
	uint8_t	n;

	i = -1;
	n = 1;
	tc = NULL;
	while (RUNNING)
	{
		read(STDIN_FILENO, &c, 1);
		ft_putchar(c);
		if (c == '\n')
			break;
		if (++i >= NORMAL_LINE * n)
			buf = strnew_realloc_buf(buf, &n);
		buf[i] = c;
	}
	if (i == -1)
		ft_memdel((void**)&buf);
	return (buf);
}

char	*read_prompt(t_tc *tc)
{
	char	*str;

	set_input_mode();
	if (!(str = ft_strnew(NORMAL_LINE)))
	{
		print_error("minishell", "could not access to termcap database", NULL, 0);
		exit(1);
	}
	str = reading(tc, str);
	reset_input_mode();
	return (str);
}