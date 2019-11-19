#include "ft_shell.h"

int mark_process_status (pid_t pid, int status)
{
    t_job *j;
    t_process *p;

    if (pid > 0)
    {
        /* Update the record for the process.  */
        for (j = g_first_job; j; j = j->next)
            for (p = j->first_process; p; p = p->next)
            if (p->pid == pid)
            {
                p->status = status;
                if (WIFSTOPPED (status))
                    p->stopped = 1;
                else
                {
                    p->completed = 1;
                    if (WIFSIGNALED (status))
                        fprintf (stderr, "%d: Terminated by signal %d.\n",
                            (int) pid, WTERMSIG (p->status));
                }
                return 0;
            }
        fprintf(stderr, "No child process %d.\n", pid);
        return -1;
    }
    else if (pid == 0)
        /* No processes ready to report.  */
        return -1;
    else {
        /* Other weird errors.  */
        perror ("waitpid");
        return -1;
    }
    return (0);
}

void update_status (void)
{
    int status;
    pid_t pid;

    do
        pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
    while (!mark_process_status (pid, status));
}

void wait_for_job (t_job *j)
{
    int status;
    pid_t pid;

    do
        pid = waitpid (WAIT_ANY, &status, WUNTRACED);
    while (!mark_process_status (pid, status)
         && !job_is_stopped (j)
         && !job_is_completed (j));
}

void format_job_info (t_job *j, const char *status)
{
  fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

void do_job_notification (void)
{
    t_job *j, *jlast, *jnext;
    //t_process *p;

    /* Update status information for child processes.  */
    update_status ();
    jlast = NULL;
    for (j = g_first_job; j; j = jnext)
    {
        jnext = j->next;

        /* If all processes have completed, tell the user the job has
         completed and delete it from the list of active jobs.  */
        if (job_is_completed (j))
        {
            format_job_info (j, "completed");
            if (jlast)
                jlast->next = jnext;
            else
                g_first_job = jnext;
            free_job(j);
        }
        /* Notify the user about stopped jobs,
         marking them so that we won't do this more than once.  */
        else if (job_is_stopped (j) && !j->notified)
        {
            format_job_info (j, "stopped");
            j->notified = 1;
            jlast = j;
        }
        /* Don't say anything about jobs that are still running.  */
        else
            jlast = j;
    }
}