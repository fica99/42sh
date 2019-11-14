#ifndef JOBS_H
# define JOBS_H

/* A process is a single process.  */
typedef struct s_process
{
    struct s_process *next;       /* next process in pipeline */
    char **argv;                /* for exec */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
}   t_process;

/* A job is a pipeline of processes.  */
typedef struct s_job
{
    struct s_job *next;           /* next active job */
    char *command;              /* command line, used for messages */
    t_process *first_process;     /* list of processes in this job */
    pid_t pgid;                 /* process group ID */
    char notified;              /* true if user told about stopped job */
    struct termios tmodes;      /* saved terminal modes */
    int stdin; 
    int stdout; /* standard i/o channels */
    int stderr;  
}   t_job;

/* The active jobs are linked into a list.  This is its head.   */
t_job *g_first_job;

pid_t g_shell_pgid;
int   g_shell_terminal;
int   g_shell_is_interactive;

/*
** init_jobs.c
*/
/* Grabbing control from terminal, setting group. */
void    init_jobs(void);
void    init_signals(void);

/*
** find_job.c
*/
/* Find the active job with the indicated pgid.  */
t_job *find_job (pid_t pgid);

/*
** job_is_stopped.c
*/
/* Return true if all processes in the job have stopped or completed.  */
int job_is_stopped (t_job *j);

/*
** job_is_completed.c
*/
/* Return true if all processes in the job have completed.  */
int job_is_completed (t_job *j);
#endif