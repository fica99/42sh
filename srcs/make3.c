/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:02:53 by filip             #+#    #+#             */
/*   Updated: 2019/04/23 21:20:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			del_symb(char *buf, short len)
{
	buf = ft_strdel_el(buf, len);
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_fd(buf + len, STDIN_FILENO);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
}

void			print_symb(char *c, char *buf, short len)
{
	short	i;

	buf = ft_stradd(buf, c, len);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_cord(buf + len);
	i = ft_strlen(buf + len) - 1;
	if (i)
		go_left(i);
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

char	*ft_stradd(char	*buf, char *s, size_t i)
{
	char	*str;

	if (i >= ft_strlen(buf))
		return (ft_strcat(buf, s));
	if (!(str = ft_strdup(buf + i)))
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	}
	*(buf + i) = '\0';
	buf = ft_strcat(ft_strcat(buf, s), str);
	ft_memdel((void**)&str);
	return (buf);
}

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		print_error("minishell", "fork() error", NULL, 0);
	return (p);
}
