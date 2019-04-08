/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/08 14:42:19 by aashara-         ###   ########.fr       */
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
	tty.c_lflag &= ~(ICANON| ECHO| ISIG);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
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
	tc->right = tgetstr("kc", NULL);
	tc->bcsp = tgetstr("kbs", NULL);
	return (tc);
}

char	*reading(t_tc *tc, char *buf)
{
	char			c[LINE_MAX + 1];
	uint8_t			n;
	ushort			nb;


	n = 1;
	tc = NULL;
	while (RUNNING)
	{
		nb = read(STDIN_FILENO, &c, LINE_MAX);
		c[nb] = '\0';
		ft_putstr_print(c);
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(buf) + ft_strlen(c) >= NORMAL_LINE * n)
			buf = strnew_realloc_buf(buf, &n);
		/*if (ft_strchr(c, '\t'))
		{
			while (!(autocom(buf, n * NORMAL_LINE)))
				buf = strnew_realloc_buf(buf, &n);
			continue ;
		}*/
		buf = ft_strcat_print(buf, c);
	}
	ft_putchar('\n');
	return (buf);
}

char	*read_prompt(t_tc *tc)
{
	char	*str;

	if (!(str = ft_strnew(NORMAL_LINE)))
	{
		print_error("minishell", "could not access to termcap database", NULL, 0);
		exit(1);
	}
	str = reading(tc, str);
	return (str);
}