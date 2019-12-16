#include "ft_shell.h"

void	add_redir(t_process *curr_proc, int fd0, int fd1)
{
	size_t i;
	int **tmp;
	int *fd;

	i = 0;
	tmp = curr_proc->redir;
	if (!(fd = (int *)malloc(sizeof(int) * 2)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	fd[0] = fd0;
	fd[1] = fd1;
	while (tmp[i])
	{
		if (i >= curr_proc->redir_size - 1)
		{
			curr_proc->redir_size *= 2;
			if (!(tmp = ft_realloc(curr_proc->redir, curr_proc->redir_size / 2, curr_proc->redir_size)))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
			free(curr_proc->redir);
			curr_proc->redir = tmp;
		}
		i++;
	}
	tmp[i] = fd;
}
