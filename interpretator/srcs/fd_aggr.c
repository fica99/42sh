#include "ft_shell.h"

// int	greater_and(int *fd, char *str)
// {
// 	if (!str)
// 	{
// 		ft_putstr("42sh: unexpected empty token: T_GREATER_AND\n");
// 		return(-1);
// 	}
// 	if (!ft_isdigit(*str))
// 		*fd = 1;
// 	else
// 		*fd = ft_atoi(str);
// 	str = ft_strchr(str, '>') + 1;
// 	if (!*str)
// 	{
// 		ft_putstr("42sh: empty file descriptor\n");
// 		return(-1);
// 	}
// 	if (*str == '-')
// 		fd[1] = open("/dev/null", RRED_OPEN, PERM_MODE);
// 	else if (ft_isdigit(*str) && ft_atoi(str) < 10)
// 		fd[1] = ft_atoi(str);
// 	else
// 		fd[1] = open(str, RRED_OPEN, PERM_MODE);
// 	return (0);
// }	 

// int	fdaggr(t_lex_tkn *redir, t_process *curr_proc)
// {
// 	int *fd;
// 	int ind;

// 	if (!(fd = (int *)malloc(sizeof(int) * 2)))
// 		err_exit("42sh", "malloc() error", NULL, NOERROR);
// 	if (redir->type == T_GREATER_AND)
// 	{
// 		if (greater_and(fd, redir->value) < 0)
// 		{
// 			free(fd);
// 			return(-1);
// 		}
// 	}
// 	// else
// 	// {
// 	// 	if (less_and(fd, redir->value) < 0)
// 	// 	{
// 	// 		free(fd);
// 	// 		reurn(-1);
// 	// 	}
// 	// }
// 	add_redir(curr_proc, fd);
// 	return(0);
// }