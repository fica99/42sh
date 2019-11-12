#include "ft_shell.h"

void    init_jobs(void)
{
    g_shell_terminal = STDIN_FILENO;
    g_shell_is_interactive = isatty(g_shell_terminal);
    g_shell_pgid = getpid();
    if (setpgid(g_shell_pgid, g_shell_pgid) < 0)
    {
        perror("Couldn't put the shell in its own process group");
        exit(1);
    }
    tcsetpgrp (g_shell_terminal, g_shell_pgid);
}