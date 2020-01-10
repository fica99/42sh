#include "ft_shell.h"

void    bg(int argc, char **argv)
{
    t_job   *j;
    int     i;

    if (argc > 0)
        i = ft_atoi(argv[1]);
    else
        i = 1;
    j = g_first_job;
    while (j && i--)
        j = j->next;
    if (j)
        put_job_in_background(j, 1);
    else
        err("42sh", "bg", argv[1], "no such job");
}