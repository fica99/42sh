/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:05:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/12 19:06:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	g_term.env_cp = copy_double_arr(environ);
	init_term();
	g_term.cord = init_cord();
	init_hash_table();
	g_term.history = make_history_buff();
	g_term.buffer = init_buff();
	term_start(&g_term);
	free_my_hash_table();
	free_history(&(g_term.history));
	reset_term();
	ft_memdel((void**)&(g_term.cord));
	ft_memdel((void**)&(g_term.buffer));
	free_double_arr(g_term.env_cp);
	return (EXIT_SUCCESS);
}

void	term_start(t_term *term)
{
	t_cord	*cord;
	
	while (RUNNING)
	{
		g_flags = INIT_FLAGS;
		signalling();
		term_prompt();
		cord = term->cord;
		get_cur_cord(cord);
		cord->prompt_len = (cord->x_cur + (cord->y_cur * cord->ws_col)) + 1;
		read_prompt(term);
		if (!(g_flags & TERM_EXIT) && !(g_flags & TERM_SIGINT))
		{
			write_history(term);
			parse_string(term);
		}
		ft_memdel((void**)&(term->buffer->buffer));
		ft_memdel((void**)&(term->buffer->save_buff));
		if (g_flags & TERM_EXIT)
			break ;
	}
}

void	term_prompt(void)
{
	char	hostname[FT_HOST_NAME_MAX];

	gethostname(hostname, FT_HOST_NAME_MAX);
	RED(STDIN_FILENO);
	ft_putchar_fd('[', STDERR_FILENO);
	CYAN(STDIN_FILENO);
	if (ft_getenv("USER"))
	{
		ft_putstr_fd(ft_getenv("USER"), STDIN_FILENO);
		RED(STDIN_FILENO);
		ft_putchar_fd('@', STDIN_FILENO);
	}
	GREEN(STDIN_FILENO);
	ft_putstr_fd(hostname, STDIN_FILENO);
	if ((check_path()))
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		YELLOW(STDIN_FILENO);
		ft_putstr_fd(check_path(), STDIN_FILENO);
	}
	RED(STDIN_FILENO);
	ft_putchar_fd(']', STDIN_FILENO);
	PURPLE(STDIN_FILENO);
	ft_putstr_fd(" $> ", STDIN_FILENO);
	STANDART(STDIN_FILENO);
}
