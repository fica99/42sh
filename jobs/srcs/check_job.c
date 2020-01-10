#include "ft_shell.h"

void mark_job_as_running (t_job *j)
{
  t_process *p;

  for (p = j->first_process; p; p = p->next)
    p->stopped = 0;
  j->notified = 0;
}

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

int job_is_stopped(t_job *j)
{
    t_process *p;

    p = j->first_process;
    while (p)
    {
		  if (!p->stopped)
			  return (0);
		  p = p->next;
    }
	return (1);
}