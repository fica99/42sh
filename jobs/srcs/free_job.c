#include "ft_shell.h"

void	free_completed_jobs(void)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (job_is_completed(j))
		{
			free_job(&g_first_job, j);
			j = g_first_job;
		}
		if (j)
			j = j->next;
	}
}

void    free_job(t_job **head, t_job *to_del)
{
	t_job *tmp;
	t_job *prev;

	if (!head || !*head)
		return ;
	if ((*head) == to_del)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp == to_del)
		{
			prev->next = tmp->next;
			free(tmp);
			tmp = prev;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}