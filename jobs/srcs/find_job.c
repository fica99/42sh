#include "ft_shell.h"

t_job   *find_job(int num)
{
    t_job *j;

    j = g_first_job;
    while (j && j->num != num)
        j = j->next;
    return (j);
}