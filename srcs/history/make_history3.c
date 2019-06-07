/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:25:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/07 16:13:52 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void    free_history(t_history **history)
{
	char    	**buf;

	buf = (*history)->history_buff;
	ft_memdel((void**)&((*history)->history_path));
	free_double_arr(buf);
	buf = NULL;
    ft_memdel((void**)history);
}

void	find_history(char **buffer, t_cord *cord, t_history *history)
{
	char	*history_search;
	char	c[LINE_MAX + 1];
	short	malloc_len;
	t_cord	*copy;
	short	i;

	(void)buffer;
	malloc_len = NORMAL_LINE;
	if (!(history_search = ft_strnew(NORMAL_LINE)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	copy = init_cord();
	get_cur_cord(copy);
	//go_right(ft_strlen(*buffer) - cord->x_cur - cord->x_start +
	//((cord->y_cur - cord->y_start) * cord->ws_col), copy);
	ft_putstr_cord("\nHistory search: ", copy);
	copy->x_start = copy->x_cur;
	copy->y_start = copy->y_cur;
	go_to_cord(cord->x_start, --(cord->y_start));
	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		if (*c == '\n' || *c == CTRL_C)
		{
			if (*c == CTRL_C)
				g_flags |= TERM_SIGINT;
			break ;
		}
		while (ft_strlen(history_search) + ft_strlen(c) >=
				(unsigned)malloc_len)
			history_search = strnew_realloc_buf(history_search,
					malloc_len += NORMAL_LINE);
		print_read(c, history_search, copy, NULL);
		if (g_flags)
			break ;
		i = -1;
		while (history->history_buff[++i])
		{
			if (ft_strstr(history_search, history->history_buff[i]))
			{
				break;
			}
		}
	}
	ft_memdel((void**)&history_search);
}