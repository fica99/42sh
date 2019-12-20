#include "ft_shell.h"

int	unset(char **av)
{
	if (av && *av)
	{
		while (++*av)
			unset_env(av, ALL_ENV);
	}
	return (0);
}