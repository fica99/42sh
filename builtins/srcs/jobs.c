#include "ft_shell.h"

void    jobs(int argc, char **argv)
{
    if (argc == 2)
    {
        if (ft_strcmp(argv[1], "-l"))
            do_job_notification(g_first_job, EXPAND_INFO);
        else if (ft_strcmp(argv[1], "-p"))
            do_job_notification(g_first_job, PID_INFO);
        else if (ft_atoi(argv[1]) != 0)
            do_job_notification(find_job(ft_atoi(argv[1])), NO_INFO);
        else
            err("42sh", "jobs", argv[1], "no such job");
    }
    else if (argc == 3)
    {
        if (!find_job(ft_atoi(argv[2])))
            err("42sh", "jobs", argv[1], "no such job");
        else if (ft_strcmp(argv[1], "-l"))
            do_job_notification(find_job(ft_atoi(argv[2])), EXPAND_INFO);
        else if (ft_strcmp(argv[1], "-p"))
            do_job_notification(find_job(ft_atoi(argv[2])), PID_INFO);
    }
    else
        do_job_notification(g_first_job, NO_INFO);
}