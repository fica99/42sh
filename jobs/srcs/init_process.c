#include "ft_shell.h"

int ft_args_len(char **args)
{
	int len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}

char	**ft_args_dup(char **args)
{
	char 	**new_args;
	int		i;

	i = 0;
	new_args = (char **)malloc(sizeof(char *) * (int)ft_args_len(args));
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

t_process *new_process(char **args)
{
	t_process *p;

	p = (t_process *)malloc(sizeof(t_process));
	p->args = ft_args_dup(args);
	p->next = NULL;
	p->pid = -1;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
	return (p);
}

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		err_exit("minishell", "fork() error", NULL, NOERROR);
	return (p);
}