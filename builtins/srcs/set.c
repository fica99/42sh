#include "ft_shell.h"

int	set(int ac, char **args)
{
	(void)ac;
	(void)args;
	
	ft_putdar(g_env.env);
	ft_putdar(g_set_env.env);
	return (0);
}