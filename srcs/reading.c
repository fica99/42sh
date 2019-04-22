/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/22 16:31:26 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include<stdio.h>

void	read_prompt(void)
{
	if (!(buffer = ft_strnew(NORMAL_LINE)))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	set_input_mode();
	reading();
	reset_input_mode();
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	reading(void)
{
	char	c[LINE_MAX + 1];
	uint8_t	n;

	n = 1;
	while (READING)
	{
		read_handler(c);
		if (g_flags)
			check_flags();
		if ((ft_strchr(c, '\n')))
			break;
		while (ft_strlen(buffer) + ft_strlen(c) >= NORMAL_LINE * n)
			buffer = strnew_realloc_buf(buffer, &n);
		print_read(c, &n);
	}
}

void	read_handler(char *c)
{
	short	nb;

	if ((nb = read(STDIN_FILENO, c, LINE_MAX)) < 0)
			print_error("minishell", "read() error", NULL, 0);
	c[nb] = '\0';
}

void	print_read(char *c, uint8_t *n)
{
	short	len;

	*n = *n;
	len = cord.x_cur - cord.prompt + (cord.y_cur * cord.ws_col);
	if (*c == CTRL_H)
		*c = BCSP;
	if (!(ft_strcmp(c, LEFT)) && len)
		go_left(1);
	else if (!(ft_strcmp(c, RIGHT)) && ((short)ft_strlen(buffer) > len))
		go_right();
	else if (*c == TAB)
		while (!(autocom(&buffer, *n * NORMAL_LINE)))
			buffer = strnew_realloc_buf(buffer, n);
	else
		print_read2(c, len);
}

void	print_read2(char *c, short len)
{
	if ((*c == BCSP && len) || !ft_strcmp(c, DEL) || *c == CTRL_D)
	{
		if (*c == BCSP)
		{
			go_left(1);
			len--;
		}
		if (!ft_strlen(buffer) && *c == CTRL_D)
			exit(EXIT_SUCCESS);
		del_symb(buffer, len);
	}
	else if (ft_isprint(*c) && *c != BCSP)
		print_symb(c, buffer, len);
}
