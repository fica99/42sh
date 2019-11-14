#include "ft_shell.h"

t_job create_job(void)
{
    
}

void launch_job(job *j, int foreground)
{
    process *p;
    pid_t   pid;

    p = j->g_first_process;
    while (p)
    {
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
        }
        p = p->next;
    }
    if (!g_shell_is_interactive)
        wait_for_job(j);
    else if (foreground)
        put_job_in_foreground(j, 0);
    else
        put_job_in_background(j, 0);
}