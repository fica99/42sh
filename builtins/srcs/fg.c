#include "ft_shell.h"

void    fg(int argc, char **argv)
{
    t_job   *j;
    int     i;

    if (argc > 0)
        i = ft_atoi(argv[1]);
    else
        i = 1;
    j = g_first_job;
    while (j && j->num != i)
        j = j->next;
    if (j)
    {
        mark_job_as_running(j);
        put_job_in_foreground(j, 1);
    }
    else
        err("42sh", "fg", argv[1], "no such job");
}
