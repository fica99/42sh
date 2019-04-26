/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/26 19:57:35 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	while (RUNNING)
	{
		signalling();
		term_prompt();
		get_cur_cord();
		g_term.x_start = g_term.x_cur;
		g_term.y_start = g_term.y_cur;
		read_prompt();
		if (!(g_flags & TERM_SIGINT))
			parse_string();
		else
			g_flags &= ~TERM_SIGINT;
		ft_memdel((void**)&(g_term.buffer));
	}
}

void		get_cur_cord(void)
{
	char	cur_cord[NORMAL_LINE];
	char	*pos;
	short	num;

	num = 0;
	set_input_mode();
	ft_putstr_fd(CUR_CORD, STDIN_FILENO);
	read_handler(cur_cord, STDOUT_FILENO);
	reset_input_mode();
	if (!(pos = ft_strchr(cur_cord, (int)'[')))
		return ; // обработать!
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.y_cur = num;
	num = 0;
	if (!(pos = ft_strchr(cur_cord, (int)';')))
		return ; // обработать!i
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.x_cur = num;
}

void	term_prompt(void)
{
	char	*path;
	char	hostname[FT_HOST_NAME_MAX];

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDERR_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	CYAN(STDIN_FILENO);
	ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd('@', STDIN_FILENO);
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(' ', STDIN_FILENO);
	YELLOW(STDIN_FILENO);
	path = check_path();
	ft_putstr_fd(path, STDIN_FILENO);
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}
