#include "ft_shell.h"

void	set(int len, char **args, char **env_cp)
{
	env(len, args, env_cp);
	env(len, args, g_set_env.env);
}