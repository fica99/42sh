#include "ft_shell.h"

void	exec_jobs(t_job *j)
{
	while (j)
	{
		if (!j->unactive)
			launch_job(j, 1);
		else 
		{
			if (j->err_message)
				ft_putln(j->err_message);
		}
		j = j->next;
	}
}
