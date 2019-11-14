#include "ft_shell.h"

void put_job_in_foreground (job *j, int cont)
{
    /* Put the job into the foreground.  */
    tcsetpgrp (shell_terminal, j->pgid);
    /* Send the job a continue signal, if necessary.  */
    if (cont)
    {
        //tcsetattr (g_shell_terminal, TCSADRAIN, &j->tmodes);
        if (kill (- j->pgid, SIGCONT) < 0)
            perror ("kill (SIGCONT)");
    }
    /* Wait for it to report.  */
    wait_for_job(j);
    /* Put the shell back in the foreground.  */
    tcsetpgrp(g_shell_terminal, g_shell_pgid);
    /* Restore the shell's terminal modes.  */
    /*tcgetattr(shell_terminal, &j->tmodes);
    tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);*/
}

void put_job_in_background (job *j, int cont)
{
  /* Send the job a continue signal, if necessary.  */
  if (cont)
    if (kill(-j->pgid, SIGCONT) < 0)
      perror("kill (SIGCONT)");
}