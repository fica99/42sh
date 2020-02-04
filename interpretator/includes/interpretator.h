/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:29:37 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/04 22:36:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>
# include <signal.h>
# include "libft.h"
# include "parser.h"
# include "error.h"
# include "variables.h"
# include "exec_hash_tables.h"
# define NO_FORK 1
# define FORK 0
# define HEREDOC_FILE "/tmp/.42sh_heredoc"
# define DEF_HEREDOC_SIZE 10
# define CUR_D "."
typedef	int			(*t_builtin)(int, char **);
typedef	int			(*t_redirect_func)(t_lex_tkn **, t_process *, int);

typedef	struct		s_her_vars
{
	char			**buf;
	size_t			buf_size;
	size_t			i;
	char			*tmp;
	char			**tmpb;

}					t_her_vars;

pid_t				g_job_pgid;
int					g_shell_terminal;
int					g_last_exit_status;
pid_t				g_shell_pgid;
/*
**					exec_jobs.c
*/
void				exec_jobs(void);
/*
**					check_job.c
*/
int					job_is_completed(t_job *j);
int					job_is_stopped(t_job *j);
/*
**					launch_job.c
*/
int					launch_builtin(t_process *p, int no_fork);
void				launch_job(t_job *j, int foreground);
/*
**					launch_builtin.c
*/
int					launch_builtin(t_process *p, int no_fork);
/*
**					launch_process.c
*/
void				ft_sub(char **args);
void				launch_process(t_process *p, pid_t pgid, int foreground);
/*
**					make_redir.c
*/
void				dup_redir(int **fd_list);
int					redir_handle(t_process *p);
/*
**					spec_symb.c
*/
char				*spec_symbols(char *args);
/*
**					io_redir.c
*/
int					l_redir(t_lex_tkn **list, t_process *curr_proc, int io_number);
int					g_redir(t_lex_tkn **list, t_process *curr_proc, int io_number);
/*
**					ft_open.c
*/
int					ft_open(char *fname, int fl);
/*
**					heredoc.c
*/
int					here_doc(t_lex_tkn **list, t_process *curr, int io_number);
/*
**					add_redir.c
*/
void				add_redir(t_process *curr_proc, int fd0, int fd1);
/*
**					fd_aggr.c
*/
int					l_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number);
int					g_aggr(t_lex_tkn **list, t_process *curr_proc, int io_number);
/*
**					pipes_routine.c
*/
void				close_pipes(t_process *p);
void				open_pipe(t_process *p, int *pipes);
/*
**					ft_pathcmp.c
*/
int					ft_pathcmp(char *p1, char *p2);
/*
**					ft_pathjoin.c
*/
char				*ft_pathjoin(char *s1, char *s2);
/*
**					get_fname.c
*/
char				*get_fname(char *arg);
/*
**					put_in.c
*/
void				put_job_in_foreground(t_job *j, int cont);
void				put_job_in_background(t_job *j, int cont);
/*
**					hndl_chld.c
*/
void				wait_for_job(t_job *j);
/*
**					uniq_env.c
*/
void				set_uniq_env(t_process *p);
/*
**					init_jobs.c
*/
void				init_jobs(void);
#endif
