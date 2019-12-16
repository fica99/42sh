#include "ft_shell.h"

void	make_pipe(t_process *p)
{
	int mypipe[2];

	while (p->next)
	{
		pipe(mypipe);
		p->outpipe = mypipe[1];
		p->next->inpipe = mypipe[0];
		p = p->next;
	}
}

void	exec_jobs(t_job *j)
{
	while (j)
	{
		if (j->first_process->next)
			make_pipe(j->first_process);
		if (!j->unactive)
			launch_job(j, 0);
		else 
		{
			if (j->err_message)
				ft_putln(j->err_message);
		}
		j = j->next;
	}
}
