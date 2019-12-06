#include "ft_shell.h"

void	unset(int len, char **args)
{
	len--;
	while (len > 0)
	{
		unset_env(args[len], ALL_ENV);
		len--;
	}
}