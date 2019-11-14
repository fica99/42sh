/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:51:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define LRED_OPEN O_RDONLY
# define RRED_OPEN O_RDWR | O_CREAT | O_TRUNC
# define DRRED_OPEN O_RDWR | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define INT_LEN 10
# define HEREDOC_FILE "/tmp/.fucking_heredoc"
# define INIT_AGGR_FD -5

volatile sig_atomic_t   chld_interrupt;

/*
**	interpretator.c
*/
void	interpret_ast(t_node *ast);
void	interpret_redir(t_node *ast);
/*
**	pipes.c
*/
void	pipe_op(t_node *ast);
void	left_child(int *pid, int *pipes, t_node *expr);
void	right_child(int *pid, int *pipes, t_node *expr);
/*
**	rredir.c
*/
void	rredir_op(t_node *ast);
void	amprred_op(t_node *ast);
int		get_expr_fd(t_node *ast);
int		open_red_file(char *name, t_token_type red_type, int acc, int mode);
void	exec_redir_command(t_node *ast, t_token_class class);
/*
**	lredir.c
*/
void	lredir_op(t_node *ast);
/*
**	dup_fd.c
*/
int		copy_fd(int fd, int new_fd);
void	restore_fd(int back_fd, int new_fd);
/*
**	aggr_fd.c
*/
void	aggr_fd_op(t_node *ast);
void	get_aggr_fd(char *str, int *left_fd, int *right_fd);
/*
**	exec.c
*/
void	make_command(char *buff);
void	find_command(char **args);
char	check_command(char **args);
char	check_bin(char **args, t_hash **bin_table, short bin_table_size);
/*
**	spec_symb.c
*/
char	*spec_symbols(char *args);
char	*tilda_expr(char *args);
char	*dollar_expr(char *args);
/*
**	parse_quotes.c
*/
char	**parse_quotes(char *buff);
char	*fill_quotes_buff(char **buff);
char	*remove_quotes(char **buff);
char	*remove_dquotes(char **buff);
/*
**	process.c
*/
void    launch_process(t_process *p, pid_t pgid, int foreground);
pid_t	make_process(void);
/*
**  job.c
*/
void launch_job(job *j, int foreground);
/*
**  fg_bg.c
*/
/* Put job j in the foreground.  If cont is nonzero,
   restore the saved terminal modes and send the process group a
   SIGCONT signal to wake it up before we block.  */
void put_job_in_foreground (job *j, int cont);

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */
void put_job_in_background (job *j, int cont);

/*
**  handle_chld_process.c
*/
/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */
int mark_process_status(pid_t pid, int status);

/* Check for processes that have status information available,
   without blocking.  */
void update_status (void);

/** Check for processes that have status information available,
   blocking until all processes in the given job have reported.  */
void wait_for_job (job *j);

/* Format information about job status for the user to look at.  */
void format_job_info(job *j, const char *status);

/* Notify the user about stopped or terminated jobs.
   Delete terminated jobs from the active job list.  */
void do_job_notification(void);

#endif
