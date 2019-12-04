/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:15:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 22:35:34 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define MAXDIR 4097
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"
# define FC_USAGE "fc: usage: fc [-e ename] [-lnr] [first] [last]"
# define FC_FLAG_L (1 << 1)
# define FC_FLAG_N (1 << 2)
# define FC_FLAG_R (1 << 3)
# define FC_FLAG_S (1 << 4)
# define FC_FLAG_ERROR (1 << 5)
# define FC_FILE_EDITOR ".42sh-fc"
# define FC_FILE_FLAGS O_RDWR | O_CREAT | O_TRUNC
# define FC_FILE_PERM S_IRUSR | S_IWUSR
char *g_curr_dir; 					/* containing current logical path or physical if -P is active */

typedef char t_flag;

void			ft_putln(char *str);
char			**check_flags(char **av, t_flag *no_links);
int				change_wdir(char *path, t_flag no_links);
int				pwd(char **av);
int				cd(char **av);
void			rewrite_cwd(char *path, t_flag no_links);			/* rewrite current logical pwd */
int				check_request(char **argv, char *path);
void			ft_echo(int argc, char **argv, char **env_cp);
void			env(int argc, char **argv, char **env_cp);
void			set(int len, char **args, char **env_cp);
void			print_bin_table(t_hash **bin_table, size_t size);
void			init_curr_pwd(void);				/* check current directory and rewrite PWD and g_curr_dir variables if it is invalid */
/*
***	fc.c
*/
void			fc_print_usage(void);
void			fc_open_editor(char *editor, char *first,
char *last, char *path);
void			fc_check_flags(int flags, char *editor,
char *first, char *last);
void			fc_check_error(int flags, char *editor,
int argc, char **argv);
void			fc(int argc, char **argv);
/*
***	fc_flags.c
*/
void			fc_flag_l(int flags, char *first, char *last);
void			fc_print_command(int flags, char *nb, char *elem);
#endif
