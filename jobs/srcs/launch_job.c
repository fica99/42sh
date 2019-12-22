#include "ft_shell.h"

void launch_job(t_job *j, int foreground)
{
    t_process   *p;
    pid_t       pid;
    int         pipes[2];

    p = j->first_process;
    if (!launch_builtin(p, NO_FORK))
        return ;
    while (p)
    {
        if (p->next)
        {
            if (pipe(pipes) < 0)
                err_exit("42sh", "pipe() error", NULL, NOERROR);
            p->outpipe = pipes[1];
            p->next->inpipe = pipes[0];
        }
        pid = make_process();
        if (pid == 0)
            launch_process(p, j->pgid, foreground);
        else
        {
            p->pid = pid;
            if (!j->pgid)
                j->pgid = pid;
            setpgid(pid, j->pgid);
            if (p->inpipe != STDIN_FILENO && close(p->inpipe) < 0)
            	err_exit("42sh", "close() error", NULL, NOERROR);
            if (p->outpipe != STDOUT_FILENO && close(p->outpipe) < 0)
            	err_exit("42sh", "close() error", NULL, NOERROR);
        }
        p = p->next;
    }
    if (foreground)
		put_job_in_foreground(j, 0);
}