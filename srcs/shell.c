/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 22:02:32 by aashara-         ###   ########.fr       */
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
		read_prompt();
		if (!(g_flags & TERM_SIGINT))
				parse_string();
		else
			g_flags &= ~TERM_SIGINT;
		ft_memdel((void**)&(g_term.buffer));
	}
}

void		get_cur_cord()
{
	char	cur_cord[100];
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

