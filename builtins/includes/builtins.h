/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:24:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 18:34:55 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define MAXDIR 4097
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"
# define FC_USAGE "fc: usage: fc [-e ename] [-lnr] [first] [last]"
# define FC_FILE_EDITOR ".42sh-fc"
# define FALSE 0
# define TRUE 1

# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "libdar.h"
# include "libdir.h"
# include "error.h"
# include "environ.h"
# include "jobs.h"
# include "term.h"
# include "hash_table.h"

char				*g_curr_dir;
typedef	int			(*t_builtin)(int, char **);
typedef char		t_flag;

typedef struct		s_keyw
{
	char			*data;
	struct s_keyw	*next;
}					t_keyw;

t_keyw				g_keyw;

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
**	bg.c
*/
void				bg(int argc, char **argv);
/*
**	cd.c
*/
void				init_curr_pwd(void);
char				**check_flags(char **av, t_flag *no_links);
int					cd(int ac, char **av);
/*
**	cdpath.c
*/
void				remove_slashes(void);
int					cdpath_handle(char *path, t_flag no_links);
/*
**	ft_pathjoin.c
*/
char				*ft_pathjoin(char *s1, char *s2);
/*
**	rewrite_cwd.c
*/
void				path_add(char *tmp);
int					change_wdir(char *path, t_flag no_links);
/*
***	echo_eflag.c
*/
int					ft_eflag(int i, char **argv, int argc, int *flags);
int					ft_isoct(char c);
int					ft_hexout(char **argv, int i, int j);
/*
***	echo.c
*/
int					ft_echo(int argc, char **argv);
int					ft_common_escape(char **argv, int i, int j);
int					ft_octal(char **argv, int i, int j);
/*
***	echo_one_escape.c
*/
int					echo_one_escape(char **argv, int i, int j);
void				echo_slashes(char **argv, int i, int j);
void				echo_text(char **argv, int i, int j);
/*
***	exit.c
*/
int					exit_built(int ac, char **av);
/*
***	export.c
*/
int					export(int ac, char **av);
/*
***	fc.c
*/
int					fc(int argc, char **argv);
/*
***	fc_parse.c
*/
char				fc_parse_args(t_fc *fc, int argc, char **argv);
/*
***	fc_exec.c
*/
void				fc_exec(t_fc *fc);
/*
**	fg.c
*/
void				fg(int argc, char **argv);
/*
**	hash.c
*/
int					hash(int ac, char **av);
/*
**	jobs.c
*/
void				jobs(int argc, char **argv);
/*
***	keywords.c
*/
char				*type_error(char *arg);
void				fill_keyw(t_keyw *keyw);
void				free_keyw(t_keyw *keyw);
/*
**	pwd.c
*/
int					pwd(int ac, char **av);
/*
**	set_var.c
*/
int					set_var(int ac, char **av);
/*
**	set.c
*/
int					set(int len, char **args);
/*
**	setenv_built.c
*/
int					setenv_built(int ac, char **av);
/*
***	type.c
*/
int					ft_type(int argc, char **argv);
/*
**	unset.c
*/
int					unset(int ac, char **args);

#endif
