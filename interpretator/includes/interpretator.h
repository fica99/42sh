/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:29:37 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/15 17:06:57 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>
# include <signal.h>
# include <glob.h>
# include <pwd.h>
# include <sys/types.h>
# include "libft.h"
# include "parser.h"
# include "error.h"
# include "variables.h"
# include "hash_tables.h"
# define NO_FORK 1
# define FORK 0
# define HEREDOC_FILE "/tmp/.42sh_heredoc"
# define DEF_HEREDOC_SIZE 10
# define CUR_D "."

typedef	int			(*t_builtin)(int, char **, char **);
typedef	int			(*t_redirect_func)(t_lex_tkn **, t_process *, int);

typedef	struct		s_her_vars
{
	char			**buf;
	size_t			buf_size;
	size_t			i;
	char			*tmp;
}					t_her_vars;

typedef enum 		e_qt
{
	QT_DQ,
	QT_SQ,
	QT_NQ
}					t_qt;


pid_t				g_job_pgid;
int					g_shell_terminal;
int					g_last_exit_status;
pid_t				g_shell_pgid;

/*
**					find_in_path.c
*/
char				*find_in_path(char *filename, char **environ);
/*
**					exec_jobs.c
*/
void				exec_jobs(void);
/*
**					check_job.c
*/
int					job_is_completed(t_job *j);
void				mark_job_as_running(t_job *j);
int					job_is_stopped(t_job *j);
/*
**					launch_job.c
*/
int					launch_builtin(t_process *p, int no_fork);
void				cls_redir(int **red);
void				launch_job(t_job *j, int foreground);
/*
**					launch_builtin.c
*/
int					launch_no_fork_builtin(t_process *p);
int					launch_fork_builtin(t_process *p);
/*
**					launch_process.c
*/
void				launch_process(t_process *p, pid_t pgid, int foreground);
/*
**					make_redir.c
*/
void				dup_redir(int **fd_list);
int					redir_handle(t_process *p);
/*
**					io_redir.c
*/
int					l_redir(t_lex_tkn **list, t_process *curr_proc,
														int io_number);
int					g_redir(t_lex_tkn **list, t_process *curr_proc,
														int io_number);
/*
**					ft_open.c
*/
int					ft_open(char *fname, int fl);
/*
**					heredoc.c
*/
int					here_doc(t_lex_tkn **list, t_process *curr,
														int io_number);
/*
**					add_redir.c
*/
void				add_redir(t_process *curr_proc, int fd0, int fd1);
/*
**					fd_aggr.c
*/
int					l_aggr(t_lex_tkn **list, t_process *curr_proc,
														int io_number);
int					g_aggr(t_lex_tkn **list, t_process *curr_proc,
														int io_number);
/*
**					pipes_routine.c
*/
void				close_pipes(t_process *p);
void				open_pipe(t_process *p, int *pipes);
/*
**					get_fname.c
*/
int					check_path_var(char *fname, char **environ);
char				*get_fname(char *arg);
/*
**					put_in.c
*/
void				put_job_in_foreground(t_job *j, int cont);
void				put_job_in_background(t_job *j, int cont);
/*
**					hndl_chld.c
*/
int					mark_process_status(pid_t pid, int status);
void				wait_for_job(t_job *j);
/*
**					uniq_env.c
*/
void				set_uniq_env(t_process *p);
/*
**					init_jobs.c
*/
void				init_jobs(void);
/*
**					chld_signals.c
*/
void				kill_info(t_process *p, int status, int foreground);
/*
**					tilda_substitutions.c
*/
char				**tilda_substitutions(char **args);
/*
**					vars_substitutions.c
*/
char				**vars_substitutions(char **args);
/*
**					quotes_managment.c
*/
t_qt				check_quotes_type(char *str, size_t pos, t_qt qt);
/*
**					pattern_substitutions.c
*/
char				**pattern_substitutions(char **args);
/*
**					substitutions.c
*/
char				**substitutions(char **args);
#endif
