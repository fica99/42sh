/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:56:55 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/27 13:29:05 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H
# define DEF_ARGS_SIZE 10
# define DEF_REDIR_SIZE 10
# define DEF_OPENFD_SIZE 10
# define NO_FORK 1
# define FORK 0
# define NO_INFO 0
# define EXPAND_INFO 1
# define PID_INFO 2
# define CUR_D "."

# include <dirent.h>
# include <signal.h>
# include "libft.h"
# include "lex.h"
# include "error.h"
# include "environ.h"
# include "hash_table.h"
# include "builtins.h"

typedef	struct			s_redir_list
{
	t_lex_tkn			**rd_token;
	struct s_redir_list	*next;
}						t_redir_list;

typedef struct			s_process
{
	struct s_process	*next;
	char				**args;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					error;
	int					**fd_list;
	t_redir_list		*r;
	char				**environment;
	int					inpipe;
	int					outpipe;
	size_t				redir_size;
	size_t				args_size;
}						t_process;

typedef struct			s_job
{
	struct s_job		*next;
	int					separator;
	int					num;
	int					notified;
	char				**command;
	t_process			*first_process;
	pid_t				pgid;
	struct termios		*tmodes;
}						t_job;

# include "interpretator.h"


t_job					*g_first_job;
t_job					*g_last_job;
int						g_last_exit_status;
pid_t					g_shell_pgid;
pid_t					g_job_pgid;
int						g_shell_terminal;
struct termios			g_shell_tmodes;

void					set_uniq_env(t_process *p);
char					**get_uniq_env(char **ue);
/*
**	launch_process.c
*/
void					launch_process(t_process *p,
		pid_t pgid, int foreground);
void					ft_sub(char **args);
void					dup_redir(int **fd_list);
int						redir_handle(t_process *p);
/*
**	ft_pathcmp.c
*/
int						ft_pathcmp(char *p1, char *p2);
/*
**	get_fname.c
*/
char					*get_fname(char *arg);
/*
**	red.c
*/
int						find_dup(int **redir, int fd);
pid_t					make_process(void);
/*
**	launch_builtin.c
*/
int						launch_builtin(t_process *p, int flag);
/*
**	launch_job.c
*/
void					launch_job(t_job *j, int foreground);
/*
**	hndl_chld.c
*/
void					do_job_notification(t_job *start_job,
		int options, int stop_flag);
void					wait_for_job(t_job *j);
void					update_status (void);
int						mark_process_status(pid_t pid, int status);
/*
**  job_print.c
*/
void					print_command(char **command);
void					format_job_info(t_job *j,
const char *status, int options);
void					completion_err(char *name,
char *str, char **command, char *err);
void					ft_completion_error(char *name,
char *str, char **command, char *err);
/*
**	put_in.c
*/
void					put_job_in_foreground(t_job *j, int cont);
void					put_job_in_background (t_job *j, int cont);
/*
**	free_job.c
*/
void					free_job(t_job **head, t_job *j);
/*
**	check_job.c
*/
int						max_job(void);
int						job_is_stopped (t_job *j);
void					mark_job_as_running (t_job *j);
int						job_is_completed (t_job *j);
/*
**	init_jobs.c
*/
void					init_jobs(void);
/*
**	find_job.c
*/
t_job					*find_job(int num);
/*
**	pipes_routine.c
*/
void					open_pipe(t_process *p, int *pipes);
void					close_pipes(t_process *p);

char					*find_in_path(char *filename);
int						check_path_var(char *fname);
/*
**	signals.c
*/
void					set_sig_def(void);

#endif
