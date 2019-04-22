#include "minishell.h"

void ft_perror(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno_f)
		pr_gen_perror();
}

void pr_gen_perror(void)
{
	int err;
	char *str[] = {
			": No such file or directory",
			": Cannot allocate memory",
			": Permission denied",
	};
	err = -1;
	if (errno_f == ENOENT)
		err = 0;
	else if (errno_f == ENOMEM)
		err = 1;
	else
		err = 2;
	ft_putstr_fd(str[err], STDERR_FILENO);
}
