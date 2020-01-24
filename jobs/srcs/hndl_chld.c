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
        while (p)
        {
    	    if (p && p->pid == pid)
    	    {
    		    p->status = status;
    		    if (WIFSTOPPED(status))
    			    p->stopped = 1;
    		    else
    		    {
    			    p->completed = 1;
    			    if (WIFSIGNALED(status))
    				    fprintf(stderr, "%d: Terminated by signal %d.\n",
    						(int)pid, WTERMSIG(p->status));
    	        }
                return (0);
            }
            p = p->next;
        }
    	j = j->next;
    }
    return (-1);
}

void update_status (void)
{
    pid_t pid;

    do
        pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED|WNOHANG);
    while (!mark_process_status(pid, g_last_exit_status));
}

void wait_for_job(t_job *j)
{
    pid_t pid;

    do {
        pid = waitpid(WAIT_ANY, &g_last_exit_status, WUNTRACED);
    } while (!mark_process_status(pid, g_last_exit_status)
         && !job_is_stopped(j)
         && !job_is_completed(j));
}

static void print_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		fprintf(stderr, "%s ", command[i]);
		i++;
	}
	fprintf(stderr, "\n");
}

void format_job_info(t_job *j, int num, const char *status, int options)
{
	if (options == NO_INFO)
	{
		fprintf(stderr, "[%d]%c %s: ", num, !j->next ? '+' : '-', status);
		print_command(j->command);
	}
	else if (options == PID_INFO)
		fprintf(stderr, "%ld\n", (long) j->pgid);
	else if (options == EXPAND_INFO)
	{
		fprintf(stderr, "[%d]%c %ld %s: ", num, !j->next ? '+' : '-', (long) j->pgid,
				status);
		print_command(j->command);
	}
}

void print_jobs(void)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		fprintf(stderr, "c = %d | s = %d ", j->first_process->completed,
				j->first_process->stopped);
		print_command(j->command);
		j = j->next;
	}
	fprintf(stderr, "\n");
}

void do_job_notification(t_job *start_job, int options)
{
    t_job 	*j;

	update_status();
	j = start_job;
	//print_jobs();
    while (j)
    {
        //fprintf(stderr, "%d\n", j->num);
        if (job_is_completed(j) && j->num > 0)
        {
            format_job_info(j, j->num, "completed", options);
            free_job(&g_first_job, j);
        }
        else if (job_is_stopped(j) && j->num > 0)
            format_job_info(j, j->num, "stopped", options);
		/*if (start_job != g_first_job)
			break ;*/
		j = j->next;
    }
}