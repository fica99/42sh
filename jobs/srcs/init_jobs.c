#include "ft_shell.h"

static void    init_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    //signal(SIGCHLD, SIG_IGN);
}

void    init_jobs(void)
{
    g_first_job = NULL;
    g_shell_terminal = STDIN_FILENO;
    init_signals();
    g_shell_pgid = getpid();
    tcgetattr(g_shell_terminal, &g_shell_tmodes);
}