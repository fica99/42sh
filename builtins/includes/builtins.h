/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:24:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/02/09 13:12:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>
# include "libft.h"
# include "libdar.h"
# include "error.h"
# include "variables.h"
# include "hash_tables.h"
# include "ft_readline.h"
# include "interpretator.h"
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"
# define FC_USAGE "fc: usage: fc [-e ename] [-lnr] [first] [last]"
# define UNALIAS_USAGE "unalias [-a] name [name ...]"
# define NO_INFO 0
# define EXPAND_INFO 1
# define PID_INFO 2

typedef char		t_flag;

typedef struct		s_fc
{
	char			*editor;
	char			*first;
	char			*last;
	int				first_i;
	int				last_i;
	char			flag_n;
	char			flag_l;
	char			flag_r;
}					t_fc;

/*
**					cd.c
*/
char				**check_flags(char **av, t_flag *no_links);
int					cd(int ac, char **av, char **environ);
/*
**					cdpath.c
*/
void				remove_slashes(void);
int					cdpath_handle(char *path, t_flag no_links, char **environ);
/*
**					rewrite_cwd.c
*/
void				path_add(char *tmp);
int					change_wdir(char *path, t_flag no_links, char **environ);
/*
**					pwd.c
*/
int					pwd(int ac, char **av, char **environ);
/*
**					echo_eflag.c
*/
int					ft_isoct(char c);
int					ft_hexout(char **argv, int i, int j);
int					ft_eflag(int i, char **argv, int argc, int *flags);
/*
**					echo.c
*/
int					ft_octal(char **argv, int i, int j);
int					ft_common_escape(char **argv, int i, int j);
int					ft_echo(int argc, char **argv, char **environ);
/*
**					echo_one_escape.c
*/
int					echo_one_escape(char **argv, int i, int j);
void				echo_slashes(char **argv, int i, int j);
void				echo_text(char **argv, int i, int j);
/*
**					exit_built.c
*/
int					exit_built(int ac, char **av, char **environ);
/*
**					hash.c
*/
int					hash(int ac, char **av, char **environ);
/*
**					set.c
*/
int					set(int ac, char **args, char **environ);
/*
**					fc.c
*/
int					fc(int argc, char **argv, char **environ);
/*
**					fc_parse.c
*/
char				fc_parse_args(t_fc *fc, int argc, char **argv);
/*
**					fc_exec.c
*/
void				fc_exec(t_fc *fc, char **environ);
/*
**					unset.c
*/
int					unset(int ac, char **args, char **environ);
/*
**					test.c
*/
int					ft_test(int argc, char **argv, char **environ);
/*
**					test_files.c
*/
int					works_with_dir(char **argv);
/*
**					test_existntype.c.c
*/
int					file_was_found(char **argv);
int					is_dir_char_block(char **argv, struct stat lstb,
struct stat stb);
int					is_pipe_link_sock_file(char **argv, struct stat lstb,
struct stat stb);
/*
**					test_rightsnset.c
*/
int					test_types(char **argv, struct stat lstb, struct stat stb);
int					rights_n_set(char **argv, struct stat lstb,
struct stat stb);
int					s_or_file(char **argv);
/*
**					test_compare.c
*/
int					iscomparison(char **argv);
/*
**					export.c
*/
int					export(int ac, char **av, char **environ);
/*
**					type.c
*/
int					ft_type(int argc, char **argv, char **environ);
/*
**					set_var.c
*/
int					set_variable(int ac, char **av, char **environ);
/*
**					jobs.c
*/
void				jobs(int argc, char **argv, char **environ);
/*
**					job_print.c
*/
void				format_job_info(t_job *j, const char *status, int options);
/*
**					free_job.c
*/
void				free_job(t_job **head, t_job *to_del);
/*
**					ft_free_jobs.c
*/
void				ft_free_proc(t_process *p);
/*
**					fg.c
*/
void				fg(int argc, char **argv, char **environ);
/*
**					bg.c
*/
void				bg(int argc, char **argv, char **environ);
/*
**					alias.c
*/
int					alias(int argc, char **argv, char **environ);
/*
**					unalias.c
*/
int					unalias(int argc, char **argv, char **environ);

#endif
