#include "ft_shell.h"

int mark_process_status(pid_t pid, int status)
{
    t_job 		*j;
    t_process 	*p;

    if (pid <= 0)
    	return (-1);
    j = g_first_job;
    while (j)
    {
    	p = j->first_process;
    	if (p && p->pid == pid)
    	{
    		p->status = status;
    		if(WIFSTOPPED(status))
    			p->stopped = 1;
    		else
    		{
    			p->completed = 1;
    			if (WIFSIGNALED(status))
    				fprintf(stderr, "%d: Terminated by signal %d.\n",
    						(int)pid, WTERMSIG(p->status));
    		}
    	}
    	j = j->next;
    }
    return (0);
}

void update_status (void)
{
    int status;
    pid_t pid;

    do
        pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
    while (!mark_process_status(pid, status));
}

void wait_for_job(t_job *j)
{
    int status;
    pid_t pid;

	job_is_stopped(j);
    do {
        pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    } while (!mark_process_status(pid, status)
         && !job_is_stopped(j)
         && !job_is_completed(j));
}

void format_job_info(t_job *j, int num, const char *status, int options)
{
	if (options == NO_INFO)
		fprintf(stderr, "[%d]%c %s: %s\n", num, !j->next ? '+' : '-', status,
					j->command);
	else if (options == PID_INFO)
		fprintf(stderr, "%ld\n", (long)j->pgid);
	else if (options == EXPAND_INFO)
		fprintf(stderr, "[%d]%c %ld %s: %s\n", num, !j->next ? '+' : '-', status, 
					(long)j->pgid, j->command);
}

void do_job_notification(t_job *start_job, int options)
{
    t_job 	*j;

	update_status();
	j = start_job;
    while (j)
    {
        if (job_is_completed(j))
        {
            format_job_info(j, j->num, "completed", options);
            free_job(j);
        }
        else if (job_is_stopped (j) && !j->notified)
        {
            format_job_info(j, j->num, "stopped", options);
            j->notified = 1;
        }
		if (start_job != g_first_job)
			break ;
		j = j->next;
    }
}