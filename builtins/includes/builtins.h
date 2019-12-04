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
#endif
