#ifndef JOBS_H
# define JOBS_H
# define DEF_ARGS_SIZE 10
# define DEF_REDIR_SIZE 10
# define DEF_OPENFD_SIZE 10
# define NO_FORK 0
# define FORK 1

// typedef struct	s_open_fd
// {
// 	int	*fd;
// 	size_t size;
// }				t_open_fd;

/* A process is a single process.  */
typedef struct s_process
{
    struct s_process *next;       /* next process in pipeline */
    char **args;                /* for exec */
    pid_t pid;                  /* process ID */
    char completed;             /* true if process has completed */
    char stopped;               /* true if process has stopped */
    int status;                 /* reported status value */
    int **redir;
    int inpipe;
    int outpipe;
    size_t redir_size;
    size_t args_size;
    // t_open_fd open_fd;
}   t_process;

/* A job is a pipeline of processes.  */
typedef struct s_job
{
    char unactive;
    char *err_message;
    struct s_job *next;           /* next active job */
    char *command;              /* command line, used for messages */
    t_process *first_process;     /* process in this job */
    pid_t pgid;                 /* process group ID */
    char notified;              /* true if user told about stopped job */
    struct termios *tmodes;      /* saved terminal modes */
}   t_job;

/* The active jobs are linked into a list.  This is its head.   */
t_job *g_first_job;

pid_t g_shell_pgid;
int   g_shell_terminal;
int   g_shell_is_interactive;
struct termios g_shell_tmodes;

int	launch_builtin(t_process *p, int flag);
/*
** init_jobs.c
*/
/* Grabbing control from terminal, setting group. */
t_job *new_job(char **args);
t_job *push_back_job(char **args);
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
/*
** free_job.c
*/
void    free_job(t_job *j);
/*
**  handle_chld_process.c
*/
/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */
int mark_process_status(pid_t pid, int status);

/* Check for processes that have status information available,
   without blocking.  */
void update_status (void);

/** Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */
void wait_for_job (t_job *j);

/* Format information about job status for the user to look at.  */
void format_job_info(t_job *j, const char *status);

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */
void do_job_notification(void);
/*
**	launch_process.c
*/
void	launch_process(t_process *p, pid_t pgid, int foreground);
/*
**  init_process.c
*/
t_process *new_process(char **args);
pid_t	make_process(void);
/*
**  launch_job.c
*/
void launch_job(t_job *j, int foreground);
/*
**  fg_bg.c
*/
/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */
void put_job_in_foreground (t_job *j, int cont);

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */
void put_job_in_background (t_job *j, int cont);
/*
**  cont_job.c
*/
/* Mark a stopped job J as being running again.  */
void mark_job_as_running (t_job *j);
/* Continue the job J.  */
void continue_job(t_job *j, int foreground);
#endif
