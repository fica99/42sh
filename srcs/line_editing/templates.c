/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   templates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:40:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/26 22:33:04 by aashara-         ###   ########.fr       */
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
	// table = push_hash(table, K_HOME, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, K_END, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, K_DEL, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, K_UP, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, K_DOWN, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, SHIFT_RGHT, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, SHIFT_LFT, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, CTRL_UP, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, CTRL_DOWN, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, CTRL_RIGHT, (void*)&, TEMPL_TABLE_SIZE);
	// table = push_hash(table, CTRL_LEFT, (void*)&, TEMPL_TABLE_SIZE);
	table = set_templ_table_symb(table);
	return (table);
}

t_hash	**set_templ_table_symb(t_hash **table)
{
	//char	symb;

	// symb = TAB;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_R;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_H;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_X;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_V;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_C;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = CTRL_D;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = BCSP;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	// symb = NEW_LINE;
	// table = push_hash(table, &symb, (void*)&, TEMPL_TABLE_SIZE);
	return (table);
}

void	find_templ(char *c, t_line *line)
{
	void	(*handler)(t_line *line);

	print_symb(c, line);
	if ((handler = get_hash_data(line->templates, c, TEMPL_TABLE_SIZE)))
		handler(line);
}
