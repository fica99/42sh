#include "ft_shell.h"

static int write_here_doc(/*t_process *curr_proc,*/ char **buf)
{
	int fd;

	fd = ft_open(HEREDOC_FILE, RRED_OPEN);
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
	char **tmpb;

	i = 0;
	buf_size = DEF_HEREDOC_SIZE;
	if (!(buf = (char **)ft_memalloc(sizeof(char *) * buf_size)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	while ((tmp = ft_readline("heredoc>", EMACS)) && ft_strcmp(tmp, delim))
	{
		buf[i++] = tmp;
		if (i >= buf_size - 1)
		{
			if (!(tmpb = (char **)ft_realloc(buf, sizeof(char *) * buf_size, sizeof(char *) * (buf_size * 2))))
				err_exit("42sh", "malloc() error", NULL, NOERROR);
			free(buf);
			buf = tmpb;
			buf_size *= 2;
		}
	}
	if (tmp)
		free(tmp);
	return (buf);
}

int here_doc(t_lex_tkn **list, t_process *curr, int io_number)
{
	char **buf;
	int fd;

	if (io_number < 0)
		io_number = 0;
	list++;
	buf = read_heredoc((*list)->value);
	fd = write_here_doc(buf);
	ft_free_dar(buf);
	add_redir(curr, fd, io_number);
	return(word_list(++list, curr));
}
