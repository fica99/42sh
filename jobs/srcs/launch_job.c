#include "ft_shell.h"

void launch_job(t_job *j, int foreground)
{
    t_process   *p;
    pid_t       pid;
    int         mypipe[2];
    p = j->first_process;
    while (p)
    {
        if (!p->args[0])
            p = p->next;
        pid = make_process();
        if (pid == 0)
            launch_process(p, j->pgid, foreground);
        else
        {
            p->pid = pid;
            if (g_shell_is_interactive)
            {
                if (!j->pgid)
                j->pgid = pid;
                setpgid(pid, j->pgid);
            }
            p = p->next;
        }
    }
    waitpid(-1, 0, 0);
//  if (g_shell_is_interactive)
    //wait_for_job(j);
    // else if (foreground)
    //     put_job_in_foreground(j, 0);
    // else
    //     put_job_in_background(j, 0);
}