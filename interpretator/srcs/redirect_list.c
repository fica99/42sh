#include "ft_shell.h"

int check_file_access(char *fname)
{
	if (access(fname, F_OK))
		ft_error("42sh", "no such file or directory", fname, NOERROR);
	else if (access(fname, W_OK | R_OK))
		ft_error("42sh", "permission denied", fname, NOERROR);
	else
		ft_error("42sh", "failed to open/create file", fname, NOERROR);
	return (-1);
}

int	ft_open(t_process *curr_proc, char *fname, int fl)
{
	int fd;
	size_t i;

	i = 0;
	if ((fd = open(fname, fl, PERM_MODE)) < 0)
		return (check_file_access(fname));
	while (curr_proc->open_fd.fd[i])
	{
		if (i >= curr_proc->open_fd.size - 2)
		{
			curr_proc->open_fd.size *= 2;
			ft_realloc(curr_proc->open_fd.fd, curr_proc->open_fd.size / 2, curr_proc->open_fd.size);
		}
		i++;
	}
	curr_proc->open_fd.fd[i] = fd;
	return(fd);
}

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
			ft_realloc(curr_proc->redir, curr_proc->redir_size / 2, curr_proc->redir_size);
			tmp = curr_proc->redir;
		}
		i++;
	}
	tmp[i] = fd;
}

static int l_redir(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fd_w;

	io_number = io_number < 0 ? 0 : io_number;
	list++;
	if ((fd_w = ft_open(curr_proc, (*list)->value, LRED_OPEN)) < 0)
		return (-1);
	add_redir(curr_proc, fd_w, io_number);
	return (redirect_list(++list, curr_proc));
}

static int write_here_doc(t_process *curr_proc, char **buf)
{
	int fd;

	fd = ft_open(curr_proc, HEREDOC_FILE, RRED_OPEN);
	if (fd < 0)
	{
		ft_free_dar(buf);
		return (-1);
	}
	while (*buf)
	{
		ft_putstr_fd(*buf++, fd);
		ft_putchar_fd('\n', fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (fd);
}

char **read_heredoc(char const *delim)
{
	char **buf;
	size_t buf_size;
	size_t i;
	char *tmp;

	i = 0;
	buf_size = DEF_HEREDOC_SIZE;
	if (!(buf = (char **)ft_memalloc(sizeof(char *) * buf_size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while ((tmp = ft_readline("heredoc>", EMACS)) && ft_strcmp(tmp, delim))
	{
		buf[i++] = tmp;
		if (i >= buf_size - 1)
		{
			buf = (char **)ft_realloc(buf, sizeof(char *) * buf_size, sizeof(char *) * (buf_size * 2));
			buf_size *= 2;
		}
	}
	return (buf);
}

static int here_doc(t_lex_tkn **list, t_process *curr, int io_number)
{
	char **buf;
	int fd;

	if (io_number < 0)
		io_number = 0;
	list++;
	buf = read_heredoc((*list)->value);
	fd = write_here_doc(curr, buf);
	ft_free_dar(buf);
	add_redir(curr, fd, io_number);
	return(redirect_list(++list, curr));
}

int	g_redir(t_lex_tkn **list, t_process *curr_proc, int io_number)
{
	int fl;
	int fd_w;

	fl = (*list)->type == T_GREATER ? RRED_OPEN : DRRED_OPEN;
	if (io_number < 0)
		io_number = 1;
	++list;
	if ((fd_w = ft_open(curr_proc, (*list)->value, fl)) < 0)
		return (-1);
	add_redir(curr_proc, fd_w, io_number);
	return (redirect_list(++list, curr_proc));
}

int parse_word(t_lex_tkn **list, t_process *curr_proc)
{
	size_t i;
	char **tmp;

	i = 0;
	tmp = curr_proc->args;
	while (tmp[i])
	{
		if (i >= curr_proc->args_size - 2)
		{
			curr_proc->args_size *= 2;
			ft_realloc(curr_proc->args, curr_proc->args_size / 2, curr_proc->args_size);
			tmp = curr_proc->args;
		}
		i++;
	}
	tmp[i] = ft_strdup((*list)->value);
	return (redirect_list(++list, curr_proc));
}

int	parse_redirect(t_lex_tkn **list, t_process *curr_proc)
{
	int io_number;
	static redirect_func red[6] = {&g_redir, &g_redir, &l_redir, &here_doc, &here_doc, &here_doc};

	io_number = -1;
	if ((*list)->type == T_IO_NUMBER)
	{
		io_number = *(*list)->value - 48;
		list++;
	}
	if ((*(list + 1))->type != T_WORD)
		return(syntax_err(*(list + 1)));
	return (red[(*list)->type - 7](list, curr_proc, io_number));
}

int redirect_list(t_lex_tkn **list, t_process *cur_proc)
{
	if ((*list)->type == T_END)
		return (0);
	else if ((*list)->type == T_IO_NUMBER || (*list)->class == C_REDIR)
		return (parse_redirect(list, cur_proc));
	else if ((*list)->type == T_WORD)
		return (parse_word(list, cur_proc));
	else
		return (syntax_err(*list));
}
