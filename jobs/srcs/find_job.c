#include "ft_shell.h"

t_job *find_job(pid_t pgid)
{
    t_job *j;

    j = g_first_job;
    while (j)
    {
        if (j->pgid == pgid)
            return (j);
        j = (j->next);
    }
    return (NULL);
}
