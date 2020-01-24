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

void	free_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		ft_strdel(&command[i]);
		i++;
	}
	free(command);
}

static void del_head(t_job **head)
{
	t_job *tmp;

	tmp = *head;
	*head = (*head)->next;
	ft_free_proc(tmp->first_process);
	free_command(tmp->command);
	free(tmp);
	tmp = NULL;
}

void    free_job(t_job **head, t_job *to_del)
{
	t_job *tmp;
	t_job *prev;

	if (!head || !*head)
		return ;
	if ((*head) == to_del)
	{
		del_head(head);
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp == to_del)
		{
			prev->next = tmp->next;
			ft_free_proc(tmp->first_process);
			free_command(tmp->command);
			free(tmp);
			tmp = NULL;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}