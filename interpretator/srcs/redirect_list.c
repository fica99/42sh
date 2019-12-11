#include "ft_shell.h"

static void	add_redir(t_process *proc, int *fd)
{
	int **tmp = proc->redir;

	while (*tmp)
		tmp++;
	*tmp = fd;
}

static int ft_open(t_lex_tkn **file, int flag)
{
	int fd;

	if ((*file)->type != T_WORD)
		return (syntax_err(*file));
	fd = open((*file)->value, flag, PERM_MODE);
	return (fd);
}

static int g_redir(t_lex_tkn **redir, t_process *curr_proc, int fl)
{
	int *fd;

	if (!(fd = (int *)malloc(sizeof(int) * 2)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	fd[1] = 1;
	// if (*(*redir)->value != '>')
	// 	fd[1] = ft_atoi((*redir)->value);
	if ((fd[0] = ft_open(redir + 1, fl)) < 0)
	{
		free(fd);
		return (-1);
	}
	add_redir(curr_proc, fd);
	split_list(redir++);
	split_list(redir++);
	return (redirect_list(redir, curr_proc));
}

static int l_redir(t_lex_tkn **redir, t_process *curr_proc)
{
	int *fd;

	if (!(fd = (int *)malloc(sizeof(int))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	fd[0] = 0;
	// if (*((*redir)->value) != '>')
	// 	fd[0] = ft_atoi((*redir)->value);
	if ((fd[1] = ft_open(redir + 1, LRED_OPEN)) < 0)
	{
		free(fd);
		return (-1);
	}
	add_redir(curr_proc, fd);
	split_list(redir++);
	split_list(redir++);
	return (redirect_list(redir, curr_proc));
}

static int parse_here_doc(int fd, t_process *proc)
{
	int *tmp;

	if (!(tmp = (int *)malloc(sizeof(int) * 2)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	tmp[1] = 0;
	*tmp = fd;
	add_redir(proc, tmp);
	return (0);
}

static int write_here_doc(char **buf)
{
	int fd;
	
	fd = open(HEREDOC_FILE, RRED_OPEN, PERM_MODE);
	if (fd < 0)
	{
		ft_putstr_fd("failed to create heredoc file\n", 2);
		return (-1);
	}
	while (*buf)
		ft_putstr_fd(*buf++, fd);
	return (fd);
}

static int here_doc(t_lex_tkn **redir, t_process *curr)
{
	char **buf;
	size_t buf_size;
	char *delim;
	size_t i;
	char *tmp;

	redir++;
	if ((*redir)->type != T_WORD)
		return (syntax_err(*redir));
	delim = (*redir)->value;
	i = 0;
	buf_size = DEF_HEREDOC_SIZE;
	if (!(buf = (char **)ft_memalloc(sizeof(char *) * buf_size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while (ft_strcmp((tmp = ft_readline("heredoc>", EMACS)), delim))
	{
		buf[i++] = tmp;
		if (i >= buf_size)
		{
			buf_size *= 2;
			buf = (char **)ft_realloc(buf, sizeof(char *) * buf_size);
		}
	}
	return (parse_here_doc(write_here_doc(buf), curr));
}

int redirect_list(t_lex_tkn **redir, t_process *cur_proc)
{
    if ((*redir)->type == T_END)
        return (0);
	else if ((*redir)->class != C_REDIR)
        return syntax_err(*redir);
    else if ((*redir)->type == T_GREATER)
		return (g_redir(redir, cur_proc, RRED_OPEN));
	else if ((*redir)->type == T_GREATER_GREATER)
		return (g_redir(redir, cur_proc, DRRED_OPEN));
	else if ((*redir)->type == T_LESS)
		return (l_redir(redir, cur_proc));
	else if ((*redir)->type == T_LESS_LESS)
		return (here_doc(redir, cur_proc));
	else
		return (0);
	//	return (fdaggr(*redir, cur_proc));
}