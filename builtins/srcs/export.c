#include "ft_shell.h"

void	export(int len, char **args)
{
	int i;

	len--;
	while (len > 0)
	{
		i = 0;
		while (args[len][i] && args[len][i] != '=')
			i++;
		if (args[len][i])
			args[len][i] = 0;
		else
			return ;
		set_env(args[len], args[len] + i + 1, ENV);
		len--;
	}
}