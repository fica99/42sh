/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/06/25 20:31:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_cord	*init_cord(void)
{
	t_cord	*cord;

	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	get_win_size(cord);
	return (cord);
}

t_buff	*init_buff(void)
{
	t_buff	*buff;

	if (!(buff = (t_buff*)malloc(sizeof(t_buff))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	buff->buffer = NULL;
	buff->malloc_len = 0;
	buff->save_buff = NULL;
	buff->save_malloc_len = 0;
	buff->copy_buff = NULL;
	buff->copy_malloc_len = 0;
	buff->history_search = NULL;
	buff->history_search_malloc_len = 0;
	buff->prev_line = NULL;
	buff->prev_line_len = 0;
	return (buff);
}

void	unset_start_pos(t_cord	*cord)
{
	cord->x_start = 0;
	cord->y_start = 0;
}

void	set_start_cord(t_cord *cord)
{
	cord->x_start = cord->x_cur;
	cord->y_start = cord->y_cur;
}

void	free_cord(t_cord **cord)
{
	ft_memdel((void**)cord);
}
