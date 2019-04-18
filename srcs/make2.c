/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/18 13:03:07 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*strnew_realloc_buf(char *str, uint8_t *n)
{
	char	*arr;

	arr = str;
	(*n)++;
	if (!(str = ft_strnew(NORMAL_LINE * (*n))))
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	}
	str = ft_strcat(str, arr);
	ft_memdel((void**)&arr);
	return (str);
}

void	reset_input_mode (void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &savetty) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}

void	go_left(void)
{
	if (cord.x_cur > 0)
		ft_putstr_fd(LEFT, STDIN_FILENO);
	else
	{
		ft_putstr_fd(PREV_LINE, STDIN_FILENO);
		ft_putstr_fd("\033[1000C", STDIN_FILENO);
		(cord.y_cur)--;
		cord.x_cur = cord.ws_col;
	}
	(cord.x_cur)--;
}

void	go_right(void)
{
	if (cord.x_cur == cord.ws_col - 1)
	{
		cord.x_cur = -1;
		(cord.y_cur)++;
		ft_putstr_fd(NEXT_LINE, STDIN_FILENO);
	}
	else
		ft_putstr_fd(RIGHT, STDIN_FILENO);
	(cord.x_cur)++;
}

char	*ft_strdel_el(char	*buf, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (buf);
	str = NULL;
	if (buf + i + 1)
	{
		if (!(str = ft_strdup(buf + i + 1)))
		{
			ft_putchar_fd('\n', STDERR_FILENO);
			reset_input_mode();
			print_error("minishell", "malloc() error", NULL, ENOMEM);
		}
	}
	*(buf + i) = '\0';
	buf = ft_strcat(buf, str);
	ft_memdel((void**)&str);
	return (buf);
}
