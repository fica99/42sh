#include "ft_shell.h"

int	unset(int ac, char **av)
{
	(void)ac;

	if (av && *av)
	{
		while (++*av)
			unset_env(*av, ALL_ENV);
	}
	return (0);
}