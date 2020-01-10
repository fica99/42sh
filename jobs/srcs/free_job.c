#include "ft_shell.h"

void    free_job(t_job *j)
{
    t_job *tmp;
    t_job *cp;

    tmp = g_first_job;
    if (!tmp || !j)
        return ;
    if (tmp == j)
    {
        g_first_job = tmp->next;
        free(tmp);
        return ;
    }
    while (tmp->next != j)
        tmp = tmp->next;
    if (tmp->next && !(tmp->next)->next)
    {
        tmp->next = NULL;
        free(tmp);
    }
    else
    {
        cp = tmp->next;
        tmp->next = (tmp->next)->next;
        free(cp);
    }
}