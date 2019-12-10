/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:55:45 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/19 18:14:02 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_job *get_last_job()
{
	t_job *tmp;

	tmp = g_first_job;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process *get_last_proc(t_job *job)
{
	t_process *tmp;

	tmp = job->first_process;
	if (!tmp)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_process *proc_new()
{
	t_process *new;
	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	if (!(new->redir = (int **)ft_memalloc(sizeof(int *) * 16)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	return (new);
}

t_process	*add_process(t_lex_tkn **token)
{
	t_process	*proc;
	t_process	*tmp;
	t_job		*last_job;

	proc = proc_new();
	last_job = get_last_job();
	tmp = get_last_proc(last_job);
	if (!tmp)
		last_job->first_process = proc;
	else
		tmp->next = proc;
	proc->args = ft_strtok((*token)->value);
    return (proc);
}

void	add_redir(t_process *proc, int *fd)
{
	int **tmp = proc->redir;

	while (*tmp)
		tmp++;
	*tmp = fd;
}

int ft_open(t_lex_tkn **file, int flag)
{
	int fd;

	if ((*file)->type != T_WORD)
		return (syntax_err(*file));
	fd = open((*file)->value, flag, PERM_MODE);
	return (fd);
}

int g_redir(t_lex_tkn **redir, t_process *curr_proc, int fl)
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

int l_redir(t_lex_tkn **redir, t_process *curr_proc)
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

int parse_here_doc(int fd, t_process *proc)
{
	int *tmp;

	if (!(tmp = (int *)malloc(sizeof(int) * 2)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	tmp[1] = 0;
	*tmp = fd;
	add_redir(proc, tmp);
	return (0);
}

int write_here_doc(char **buf)
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

int here_doc(t_lex_tkn **redir, t_process *curr)
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

int simp_command(t_lex_tkn **list)
{
    t_process *curr_proc;

	if ((*list)->type == T_END)
		return (0);
	curr_proc = add_process(find_token(list, C_WORD));
    return (redirect_list(find_token(list, C_REDIR), curr_proc));
}

int	pipe_sequence(t_lex_tkn **list)
{
	t_lex_tkn **tmp;

	if ((*list)->type == T_END)
		return (0);
	if ((*list)->class == C_PIPE)
		return (syntax_err(*list));
	tmp = split_list(find_token(list, C_PIPE));
	if ((simp_command(list) < 0))
		return (-1);
	return (pipe_sequence(tmp));
}

int	logical_list(t_lex_tkn **list)
{
	// t_lex_tkn **tmp;

	// if (!*list)
	// 	return (0);
	// if ((*list)->class == C_LOGICAL)
	// 	return (syntax_err(list));
	// tmp = find_token(list, LOGICAL);
	// add_logical(tmp);
	// tmp = split_list(tmp);
	
	if ((pipe_sequence(list)) < 0)
		return (-1);
	return (0);
	// return (logical_list(tmp));
}

int	start(t_lex_tkn **list)
{
	t_lex_tkn **tmp;

	if ((*list)->type == T_END)
		return (0);
	if ((*list)->type == T_SEP)
		return (syntax_err(*list));
	job_new();
	tmp = split_list(find_token(list, C_SEP));
	if ((logical_list(list)) < 0)
		return (-1);
	return (start(tmp));
}

void print_proc(t_job *job)
{
	t_process *proc = job->first_process;

	while (proc && proc->args)
	{
		printf("*********************\n");
		while (*proc->args)
		{
			printf("%s\n", *proc->args);
			proc->args++;
		}
		while (*proc->redir)
		{
			printf("%d <== %d\n", (*proc->redir)[0], (*proc->redir)[1]);
			proc->redir++;
		}
		printf("*********************\n");
		proc = proc->next;
	}
}

void print_jobs()
{
	int i = 0;

	while (g_first_job)
	{
		printf("job %i\n", i);
		print_proc(g_first_job);
		g_first_job = g_first_job->next;
		i++;
	}
}

void	parse(t_lex_tkn **tokens)
{
	if (!*tokens || (*tokens)->type == C_END)
		return ;
	lex_print_tkns(tokens);
	return;
	start(tokens);
	print_jobs();
}
