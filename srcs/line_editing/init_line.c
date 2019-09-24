/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 19:44:33 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/26 23:36:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_line(t_line *line)
{
	line->templates = init_templates();
	line->cord = init_cord();
	init_buff(&line->copy_buff);
	init_buff(&line->buffer);
	init_buff(&line->history_search);
	init_buff(&line->save_buff);
	init_buff(&line->her_buff);
}

void	init_buff(t_buff *buffer)
{
	if (!(buffer->buffer = ft_strnew(NORMAL_LINE)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	buffer->malloc_len = NORMAL_LINE;
}

t_cord	*init_cord(void)
{
	t_cord	*cord;

	if (!(cord = (t_cord*)malloc(sizeof(t_cord))))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	cord->x_cur = 0;
	cord->x_start = 0;
	cord->ws_col = 0;
	cord->ws_row = 0;
	cord->y_cur = 0;
	cord->y_start = 0;
	cord->pos = 0;
	cord->highlight_pos = 0;
	cord->x_end = 0;
	cord->y_end = 0;
	return (cord);
}

t_hash	**init_templates(void)
{
	if (!TRANSMIT_MODE || !CUR_CORD || !ENTER_INSERT_MODE || !EXIT_INSERT_MODE || !ENTER_AM_MODE ||
	!K_LFT || !K_HOME || !K_RGHT || !K_END || !SET_CUR || !SAVE_CUR ||
	!RESTORE_CUR || !CLEAR_END_SCREEN || !CLEAR_SCREEN || !K_DEL ||
	!K_UP || !K_DOWN || !SHIFT_LFT || !SHIFT_RGHT || !STOP_TRANSMIT_MODE
	|| !CUR_RIGHT || !CUR_LFT)
		err_exit(g_argv[0], "no correct capabilities", NULL, NOERROR);
	ft_putstr_fd(ENTER_AM_MODE, STDIN_FILENO);
	return (set_templ_table());
}
