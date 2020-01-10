#include "ft_shell.h"

int job_is_completed (t_job *j)
{
    t_process *p;

    p = j->first_process;
    while (p)
    {
        if (!p->completed)
            return (0);
        p = p->next;
    }
    return (1);
}

int job_is_stopped (t_job *j)
{
    t_process *p;

    p = j->first_process;
    while (p)
    {
		  if (!p->completed && !p->stopped)
			  return (0);
		  p = p->next;
    }
	return (1);
}