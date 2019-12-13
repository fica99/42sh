#include "ft_shell.h"

void    ft_free_redir(int **red)
{
    int i;

    if (!red)
        return ;
    i = -1;
    while (red[++i])
        free(red[i]);
    free(red);
}

void    ft_free_proc(t_process *p)
{
    if (!p)
        return ;
    ft_free_proc(p->next);
    if (p->args)
        ft_free_dar(p->args);
    if (p->open_fd.fd)
        free(p->open_fd.fd);
    ft_free_redir(p->redir);
    free(p);
}

void    ft_free_jobs(t_job *j)
{
    if (!j)
        return ;
    ft_free_jobs(j->next);
    ft_free_proc(j->first_process);
    if (j->command)
        free(j->command);
    free(j);
}
