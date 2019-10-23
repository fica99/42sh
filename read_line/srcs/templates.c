/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:40:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:55:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash	**set_templ_table(void)
{
	t_hash	**table;

	if (!(table = init_hash_table(TEMPL_TABLE_SIZE)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	table = push_hash(table, K_LFT, (void*)&k_left, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_RGHT, (void*)&k_right, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_HOME, (void*)&k_home, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_END, (void*)&k_end, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_DEL, (void*)&k_del, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_UP, (void*)&k_up, TEMPL_TABLE_SIZE);
	table = push_hash(table, K_DOWN, (void*)&k_down, TEMPL_TABLE_SIZE);
	table = push_hash(table, SHIFT_RGHT, (void*)&k_shift_right,
	TEMPL_TABLE_SIZE);
	table = push_hash(table, SHIFT_LFT, (void*)&k_shift_left, TEMPL_TABLE_SIZE);
	table = push_hash(table, CTRL_UP, (void*)&k_ctrl_up, TEMPL_TABLE_SIZE);
	table = push_hash(table, CTRL_DOWN, (void*)&k_ctrl_down, TEMPL_TABLE_SIZE);
	table = push_hash(table, CTRL_RIGHT, (void*)&k_ctrl_right,
	TEMPL_TABLE_SIZE);
	table = push_hash(table, CTRL_LEFT, (void*)&k_ctrl_left, TEMPL_TABLE_SIZE);
	table = set_templ_table_symb(table);
	return (table);
}

t_hash	**set_templ_table_symb(t_hash **table)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = TAB;
	table = push_hash(table, symb, (void*)&k_tab, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_R;
	table = push_hash(table, symb, (void*)&k_ctrl_r, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_H;
	table = push_hash(table, symb, (void*)&k_bcsp, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_X;
	table = push_hash(table, symb, (void*)&k_ctrl_x, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_V;
	table = push_hash(table, symb, (void*)&k_ctrl_v, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_C;
	table = push_hash(table, symb, (void*)&k_ctrl_c, TEMPL_TABLE_SIZE);
	symb[0] = CTRL_D;
	table = push_hash(table, symb, (void*)&k_ctrl_d, TEMPL_TABLE_SIZE);
	symb[0] = BCSP;
	table = push_hash(table, symb, (void*)&k_bcsp, TEMPL_TABLE_SIZE);
	symb[0] = NEW_LINE;
	table = push_hash(table, symb, (void*)&k_enter, TEMPL_TABLE_SIZE);
	return (table);
}

void	find_templ(char *c, t_line *line)
{
	void	(*handler)(t_line *line);
	short	len;

	if (ft_isprint(*c) && !(g_line_flags & HISTORY_SEARCH))
		print_symb(c, line);
	else if (ft_isprint(*c) && (g_line_flags & HISTORY_SEARCH))
	{
		check_malloc_len_buffer(&line->history_search, c);
		ft_strcat(line->history_search.buffer, c);
		find_history(line);
	}
	else if (*c == BCSP && (g_line_flags & HISTORY_SEARCH))
	{
		if ((len = ft_strlen(line->history_search.buffer)))
			line->history_search.buffer =
			ft_strdel_el(line->history_search.buffer, len - 1);
		find_history(line);
	}
	else if ((handler = get_hash_data(line->templates, c, TEMPL_TABLE_SIZE)))
		handler(line);
}
