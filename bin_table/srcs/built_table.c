#include "ft_shell.h"

void	init_built_table(t_table *g_built_table)
{
	t_hash **table;
	
	g_built_table->size = BUILT_NUM;
	table = init_hash_table(BUILT_NUM);
	push_hash(table, "pwd", &pwd, BUILT_NUM);
	push_hash(table, "cd", &cd, BUILT_NUM);
	push_hash(table, "fc", &fc, BUILT_NUM);
	push_hash(table, "echo", &ft_echo, BUILT_NUM);
	push_hash(table, "unsetenv", &unset, BUILT_NUM);
	push_hash(table, "env", &env, BUILT_NUM);
	push_hash(table, "exit", &exit_built, BUILT_NUM);
	g_built_table->table = table;
}