#include "ft_shell.h"

// int count_proc(t_process *p)
// {
//     int res;

//     res = 0;
//     while (p)
//     {
//         res++;
//         p = p->next;
//     }
//     return (res);
// }

// int **make_pipe(t_process *p)
// {
//     int **pipes;
//     int *fd;
//     int i;

//     i = 0;
//     if (!(pipes = (int **)malloc(sizeof(int *) * count_proc(p) - 1)))
//         err_exit("42sh", "malloc() error", NULL, NOERROR);
//     while (p->next)
//     {
//         if (!(fd = (int *)malloc(sizeof(int) * 2)))
//             err_exit("42sh", "malloc() error", NULL, NOERROR);
//         pipe(fd);
//         pipes[i++] = fd;
//         p->outpipe = fd[1];
//         p->next->inpipe = fd[0];
//         p = p->next;
//     }
//     return (pipes);
// }

// void pr(int sig)
// {
//     (void)sig;
//     wait(0);
// }

void launch_job(t_job *j, int foreground)
{
   // int status;
    t_process   *p;
    pid_t       pid;
    int pipes[2];

    p = j->first_process;
    if (!launch_builtin(p, NO_FORK))
        return ; 
    while (p)
    {
        if (p->next)
        {
            pipe(pipes);
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
                close(p->inpipe);
            if (p->outpipe != STDOUT_FILENO)
                close(p->outpipe);
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