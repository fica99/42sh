/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:56:55 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 16:10:14 by mmarti           ###   ########.fr       */
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
	int					status;
	int					**fd_list;
	t_redir_list		*r;
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
	char				*command;
	t_process			*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		*tmodes;
}						t_job;

void					ft_sub(char **args);
void					dup_redir(int **fd_list);
int						redir_handle(t_process *p);

t_job					*g_first_job;
t_job					*g_last_job;
int					g_last_exit_status;

pid_t					g_shell_pgid;
int						g_shell_terminal;
int						g_shell_is_interactive;
struct termios			g_shell_tmodes;

int						ft_pathcmp(char *p1, char *p2);
char					*get_fname(char *arg);
int						find_dup(int **redir, int fd);
void					redir(int **red);

int						launch_builtin(t_process *p, int flag);

void					launch_process(t_process *p,
						pid_t pgid, int foreground);

t_process				*new_process(char **args);

pid_t					make_process(void);

void					launch_job(t_job *j, int foreground);

void do_job_notification(t_job *start_job, int options);
void format_job_info(t_job *j, int num, const char *status, int options);
void wait_for_job(t_job *j);
void update_status (void);
int mark_process_status(pid_t pid, int status);

void put_job_in_foreground(t_job *j, int cont);
void put_job_in_background (t_job *j, int cont);

void    free_job(t_job *j);

int job_is_stopped (t_job *j);
void mark_job_as_running (t_job *j);
int job_is_completed (t_job *j);

void    init_jobs(void);

t_job   *find_job(int num);

#endif
