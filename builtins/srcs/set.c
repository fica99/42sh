#include "ft_shell.h"

void	set(int len, char **args, char **env_cp)
{
	int j;

	j = 0;
	env(len, args, env_cp);
	while (g_set_env.env[j] && j < g_set_env.ar_size)
	{
		ft_putstr(g_set_env.env[j]);
		ft_putchar('\n');
		j++;
	}
}