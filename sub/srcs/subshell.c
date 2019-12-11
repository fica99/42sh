#include "ft_shell.h"

int subshell_expr(char *line)
{
	char *sub_line;
	int i;

	i = 0;
	while (line[i] && line[i] != ')')
		i++;
	if (line[i] != ')')
		return (0);
	line[i] = 0;
	sub_line = ft_strdup(line + 1);
	launch_subshell(sub_line);
	return (1);
}

void	launch_subshell(char *sub_line)
{
	pid_t p;
	int status;

	p = make_process();
	if (p == 0)
	{
		check_valid_string(sub_line);
		exit(0);
	}
	waitpid(p, &status, 0);
}