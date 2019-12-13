#include "ft_shell.h"

static void	cls_redir(int **red)
{
	int *tmp;

	while (*red)
	{
		tmp = *red;
		if (*tmp > 2)
			close(*tmp);
		if (tmp[1] > 2)
			close(tmp[1]);
		red++;
	}
}

void close_fds(t_job *first_job)
{
	t_process *tmp;
	while (first_job)
	{
		tmp = first_job->first_process;
		while (tmp)
		{
			cls_redir(tmp->redir);
			tmp = tmp->next;
		}
		first_job = first_job->next;
	}
	//todo
	// переделать
}
