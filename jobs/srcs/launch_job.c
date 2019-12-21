#include "ft_shell.h"

void launch_job(t_job *j, int foreground)
{
   // int status;
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
            if (g_shell_is_interactive)
            {
                if (!j->pgid)
                j->pgid = pid;
                setpgid(pid, j->pgid);
            }
            if (p->inpipe != STDIN_FILENO)
                if (close(p->inpipe) < 0)
                    err_exit("42sh", "close() error", NULL, NOERROR);
            if (p->outpipe != STDOUT_FILENO)
                if (close(p->outpipe) < 0)
                    err_exit("42sh", "close() error", NULL, NOERROR);
        }
        p = p->next;
    }
    while (waitpid(-1, 0, 0) != -1)
        ;
    // if (waitpid(-1, &status, 0) < 0)
    //     perror("waitpid");
    // else
    //     ft_putnbr(status);
    // if (g_shell_is_interactive)
    //     wait_for_job(j);
    // else if (foreground)
    //     put_job_in_foreground(j, 0);
    // else
    //     put_job_in_background(j, 0);
}