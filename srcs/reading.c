/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/19 22:55:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include<stdio.h>

char	*read_prompt()
{
	char	*str;

	if (!(str = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	set_input_mode();
	str = reading(str);
	reset_input_mode();
	ft_putchar_fd('\n', STDIN_FILENO);
	return (str);
}

char	*reading(char *buf)
{
	char	c[LINE_MAX + 1];
	uint8_t	n;

	n = 1;
	while (READING)
	{
		read_handler(c);
		if (g_flags & SHELL_SIGINT || g_flags & SHELL_SIGQUIT)
		{
			if (g_flags & SHELL_SIGINT)
				ft_strclr(buf);
			g_flags &= ~SHELL_SIGINT;
			g_flags &= ~SHELL_SIGQUIT;
		}
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(buf) + ft_strlen(c) >= NORMAL_LINE * n)
			buf = strnew_realloc_buf(buf, &n);
		buf = make_buf_print(buf , c, &n);
	}
	return (buf);
}

void	read_handler(char *c)
{
	short	nb;

	if ((nb = read(STDIN_FILENO, c, LINE_MAX)) < 0)
			print_error("minishell", "read() error", NULL, 0);
	c[nb] = '\0';
}

char	*make_buf_print(char *buf, char *c, uint8_t *n)
{
	short	len;

	*n = *n;
	len = cord.x_cur - cord.prompt + (cord.y_cur * cord.ws_col);
	if (*c == CTRL_H)
		*c = BCSP;
	if (!(ft_strcmp(c, LEFT)) && len)
		go_left(1);
	else if (!(ft_strcmp(c, RIGHT)) && ((short)ft_strlen(buf) > len))
		go_right();
	else
		check_key(c, buf, len);
	return (buf);
}

void			check_key(char *c, char *buf, short len)
{
	if ((*c == BCSP && len) || !ft_strcmp(c, DEL) || *c == CTRL_D)
	{
		if (*c == BCSP)
		{
			go_left(1);
			len--;
		}
		if (!ft_strlen(buf) && *c == CTRL_D)
			exit(EXIT_SUCCESS);
		del_symb(buf, len);
	}
	else if (ft_isprint(*c) && *c != BCSP)
		print_symb(c, buf, len);
}
