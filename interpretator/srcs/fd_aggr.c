#include "ft_shell.h"

int	get_fd(char *str)
{
	int fd;
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	fd = ft_atoi(str);
	return (fd);
}

int g_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number > 0 ? io_number : 1;
	++list;
	if (!ft_strcmp((*list)->value, "-"))
		fd_w = -1;
	else if ((fd_w = get_fd((*list)->value)) < 0)
		return (g_redir(--list, curr_proc, io_number));
	else if (fd_w > 2 && fd_w != io_number)
	{
		file_err("42sh: ", (*list)->value, ": Bad file descriptor", g_first_job);
		return (0);
	}
	add_redir(curr_proc, fd_w, io_number);
	return (redirect_list(++list, curr_proc));
}

int l_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number > 0 ? io_number : 0;
	++list;
	if (!ft_strcmp((*list)->value, "-"))
		fd_w = -1;
	else if ((fd_w = get_fd((*list)->value)) < 0)
	{
		file_err("42sh: ", (*list)->value, ": ambiguous redirect", g_first_job);
		return (0);
	}
	else if (fd_w > 2 && fd_w != io_number)
	{
		file_err("42sh: ", (*list)->value, ": Bad file descriptor", g_first_job);
		return (0);
	}
	add_redir(curr_proc, fd_w, io_number);
	return (redirect_list(++list, curr_proc));
}