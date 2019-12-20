#include "ft_shell.h"

void	init_built_table(t_table *g_built_table)
{
	t_hash **table;
	size_t size;

	size = 4;
	g_built_table->size = size;
	table = init_hash_table(size);
	push_hash(table, "pwd", &pwd, size);
	push_hash(table, "cd", &cd, size);
	push_hash(table, "fc", &fc, size);
	push_hash(table, "echo", &ft_echo, size);
	g_built_table->table = table;
}