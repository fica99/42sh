/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:35:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/20 13:42:53 by filip            ###   ########.fr       */
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

void	go_left(short i)
{
	short	change;

	if (cord.x_cur - i >= 0)
	{
		cord.x_cur -= i;
		ft_putstr_fd("\033[", STDIN_FILENO);
		ft_putnbr_fd(i, STDIN_FILENO);
		ft_putchar_fd('D',STDIN_FILENO);
	}
	else
	{
		change = cord.x_cur;
		while (change < i)
		{
			change += cord.ws_col;
			ft_putstr_fd(PREV_LINE, STDIN_FILENO);
			cord.y_cur--;
		}
		cord.x_cur = change - i;
		go_to(cord.x_cur);
	}
}

void	go_to(short i)
{
	ft_putstr_fd("\033[", STDIN_FILENO);
	ft_putnbr_fd(i, STDIN_FILENO);
	ft_putchar_fd('C',STDIN_FILENO);
}

void	go_right(void)
{
	if (cord.x_cur >= cord.ws_col - 1)
	{
		cord.x_cur = -1;
		(cord.y_cur)++;
		ft_putstr_fd(NEXT_LINE, STDIN_FILENO);
	}
	else
		ft_putstr_fd(RIGHT, STDIN_FILENO);
	(cord.x_cur)++;
}
