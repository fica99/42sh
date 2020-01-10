#include "ft_shell.h"

void    free_job(t_job *to_del)
{
    t_job *lst;
	t_job *tmp;
	int i = 0;

	if (g_first_job)
		return ;
	tmp = g_first_job;
    lst = g_first_job;
	while (to_del == lst)
	{
		tmp = (g_first_job)->next;
		free(g_first_job);
		(g_first_job) = tmp;
	}
	lst = g_first_job;
	tmp = g_first_job;
	while (lst != NULL)
	{
		if (lst == to_del)
		{
			tmp->next = lst->next;
			free(lst);
			lst = tmp;
			i = 0;
		}
		if (i > 0)
			tmp = tmp->next;
		if (lst != NULL)
			lst = lst->next;
		i++;
	}
}