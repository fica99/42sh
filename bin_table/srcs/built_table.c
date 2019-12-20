#include "ft_shell.h"

void	init_built_table(t_table *g_built_table)
{
	t_hash **table;

	g_built_table->size = 4;
	table = init_hash_table(4);
	push_hash(table, "pwd", &pwd, 4);
	push_hash(table, "cd", &cd, 4);
	push_hash(table, "fc", &fc, 4);
	push_hash(table, "echo", &ft_echo, 4);
	g_built_table->table = table;
}