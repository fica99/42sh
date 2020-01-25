/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:24:22 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/24 18:04:07 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define MAXDIR 4097
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"
# define FC_USAGE "fc: usage: fc [-e ename] [-lnr] [first] [last]"
# define FC_FILE_EDITOR ".42sh-fc"

char			*g_curr_dir;
typedef			int(*t_builtin)(int, char **);
typedef char	t_flag;
int				set_var(int ac, char **av);
void			path_add(char *tmp);
void			remove_slashes(void);
int				cdpath_handle(char *path, t_flag no_links);
int				setenv_built(int ac, char **av);
int				exit_built(int ac, char **av);
char			*ft_pathjoin(char *s1, char *s2);
void			ft_putln(char *str);
char			**check_flags(char **av, t_flag *no_links);
int				change_wdir(char *path, t_flag no_links);
int				pwd(int ac, char **av);
int				cd(int ac, char **av);
void			rewrite_cwd(char *path);
int				check_request(char **argv, char *path);
int				ft_echo(int argc, char **argv);
int				env(int argc, char **argv);
int				set(int len, char **args);
int				unset(int ac, char **args);
void			export(int len, char **args);
void			print_bin_table(t_hash **bin_table, size_t size);
int				hash(int ac, char **av);
void			init_curr_pwd(void);

char *g_curr_dir;

typedef int(*t_builtin)(int, char **);

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

int					set_var(int ac, char **av);
void				path_add(char *tmp);
void				remove_slashes(void);
int					cdpath_handle(char *path, t_flag no_links);
int					setenv_built(int ac, char **av);
int					exit_built(int ac, char **av);
char				*ft_pathjoin(char *s1, char *s2);
void				ft_putln(char *str);
char				**check_flags(char **av, t_flag *no_links);
int					change_wdir(char *path, t_flag no_links);
int					pwd(int ac, char **av);
int					cd(int ac, char **av);
void				rewrite_cwd(char *path);
int					check_request(char **argv, char *path);
int					env(int argc, char **argv);
int					set(int len, char **args);
int					unset(int ac, char **args);
int					export(int ac, char **av);
void				print_bin_table(t_hash **bin_table, size_t size);
int					hash(int ac, char **av);
void				init_curr_pwd(void);

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
***	type.c
*/
int					ft_type(int argc, char **argv);
/*
***	keywords.c
*/
char				*type_error(char *arg);
void				fill_keyw(t_keyw *keyw);
/*
**	jobs.c
*/
void			jobs(int argc, char **argv);
/*
**	bg.c
*/
void			bg(int argc, char **argv);
/*
**	fg.c
*/
void			fg(int argc, char **argv);

#endif
