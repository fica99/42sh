#include "ft_shell.h"

static void    init_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}

void    init_jobs(void)
{
    /*g_first_job = NULL;
    g_shell_terminal = STDIN_FILENO;
    fprintf(stderr, "%d\n", isatty(g_shell_terminal));
    while(tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
        kill(-g_shell_pgid, SIGTTIN);*/
    init_signals();
    /*g_shell_pgid = getpid();
    setpgid(g_shell_pgid, g_shell_pgid);
    tcsetpgrp(g_shell_terminal, g_shell_pgid);*/
}