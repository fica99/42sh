#include "ft_shell.h"

void    init_shell(char **argv, char **environ)
{
    init_global_var(argv, environ);
    rl_init_terminfo();
    init_jobs();
}