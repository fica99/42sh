#include "ft_shell.h"

t_job *new_job(char **args)
{
    t_job *j;

    j = (t_job *)malloc(sizeof(t_job));
    j->command = ft_strdup(args[0]);
    j->pgid = getpgrp();
    j->first_process = new_process(args);
    j->tmodes = &g_shell_tmodes;
    j->next = NULL;
    j->notified = 0;
    j->fdin = STDIN_FILENO;
    j->fdout = STDOUT_FILENO;
    j->fderr = STDERR_FILENO;
    return (j);
}

t_job *push_back_job(char **args)
{
    t_job *tmp;

    if (!g_first_job)
    {
        g_first_job = new_job(args);
        return (g_first_job);
    }
    else
    {
        tmp = g_first_job;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_job(args);
    }
    return (tmp->next);
}

void    init_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

void    init_jobs(void)
{
    g_first_job = NULL;
    g_shell_terminal = STDIN_FILENO;
    g_shell_is_interactive = isatty(g_shell_terminal);
    if (g_shell_is_interactive)
    {
        while(tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
            kill(-g_shell_pgid, SIGTTIN);
        init_signals();
        g_shell_pgid = getpid();
        if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
        {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }
        tcsetpgrp(g_shell_terminal, g_shell_pgid);
        tcgetattr(g_shell_terminal, &g_shell_tmodes);
    }
}