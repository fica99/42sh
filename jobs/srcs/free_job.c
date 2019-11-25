#include "ft_shell.h"

void    free_job(t_job *j)
{
    j->pgid = (pid_t)0;
}