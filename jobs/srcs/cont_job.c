#include "ft_shell.h"

void mark_job_as_running(t_job *j)
{
    t_process *p;

    for(p = j->first_process; p; p = p->next)
        p->stopped = 0;
    j->notified = 0;
}

void continue_job(t_job *j, int foreground)
{
    mark_job_as_running(j);
    if (foreground)
        put_job_in_foreground (j, 1);
    else
        put_job_in_background (j, 1);
}