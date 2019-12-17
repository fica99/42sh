#include "ft_shell.h"

static int check_file_access(char *fname)
{
	if (access(fname, F_OK))
		file_err("42sh: ", "no such file or directory: ", fname, g_first_job);
	else if (access(fname, W_OK | R_OK))
		file_err("42sh: ", "permission denied: ", fname, g_first_job);
	else
		file_err("42sh: ", "failed to open/create file: ", fname, g_first_job);
	return (0);
}

int	ft_open(/*t_process *curr_proc,*/char *fname, int fl)
{
	int fd;
	size_t i;

	i = 0;
	if ((fd = open(fname, fl, PERM_MODE)) < 0)
		return (check_file_access(fname));
	// while (curr_proc->open_fd.fd[i])
	// {
	// 	if (i >= curr_proc->open_fd.size - 2)
	// 	{
	// 		curr_proc->open_fd.size *= 2;
	// 		ft_realloc(curr_proc->open_fd.fd, curr_proc->open_fd.size / 2, curr_proc->open_fd.size);
	// 	}
	// 	i++;
	// }
	// curr_proc->open_fd.fd[i] = fd;
	return(fd);
}