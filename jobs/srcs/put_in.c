#include "ft_shell.h"

void    put_job_in_foreground(t_job *j, int cont)
{
    tcsetpgrp(g_shell_terminal, j->pgid);
    if (cont)
    {
        tcsetattr(g_shell_terminal, TCSADRAIN, j->tmodes);
        kill(-j->pgid, SIGCONT);
    }
    wait_for_job(j);
    tcsetpgrp(g_shell_terminal, g_shell_pgid);
    tcgetattr(g_shell_terminal, j->tmodes);
    tcsetattr(g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
}

void put_job_in_background (t_job *j, int cont)
{
	if (cont)
		kill(-j->pgid, SIGCONT);
}