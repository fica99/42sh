/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:06:15 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/22 15:17:14 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	init_built_table(t_table *g_built_table)
{
	t_hash **table;

	g_built_table->size = BUILT_NUM;
	table = init_hash_table(BUILT_NUM);
	push_hash(table, "pwd", &pwd, BUILT_NUM);
	push_hash(table, "cd", &cd, BUILT_NUM);
	push_hash(table, "echo", &ft_echo, BUILT_NUM);
	push_hash(table, "unsetenv", &unset, BUILT_NUM);
	push_hash(table, "env", &env, BUILT_NUM);
	push_hash(table, "exit", &exit_built, BUILT_NUM);
	push_hash(table, "setenv", &setenv_built, BUILT_NUM);
	push_hash(table, "hash", &hash, BUILT_NUM);
	push_hash(table, "set", &set, BUILT_NUM);
	push_hash(table, "set_var", &set_var, BUILT_NUM);
	push_hash(table, "fc", &fc, BUILT_NUM);
	push_hash(table, "type", &ft_type, BUILT_NUM);
	push_hash(table, "export", &export, BUILT_NUM);
	push_hash(table, "unset", &unset, BUILT_NUM);
	g_built_table->table = table;
}
