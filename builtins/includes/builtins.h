/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:15:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 11:20:18 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define MAXDIR 4097
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"

char *g_curr_dir; 					/* containing current logical path or physical if -P is active */

typedef char t_flag;

int				change_wdir(char *path, t_flag no_links);
void			pwd(char **av);
void			cd(char **av);
void			rewrite_cwd(char *path, t_flag no_links);			/* rewrite current logical pwd */
char			check_request(char **argv, char *path);
void			ft_echo(int argc, char **argv, char **env_cp);
void			env(int argc, char **argv, char **env_cp);
void			set(int len, char **args, char **env_cp);
void			print_bin_table(t_hash **bin_table, size_t size);
void			set_env(int argc, char **argv, char **env_cp);
void			unset_env(int argc, char **argv, char **env_cp);
void			init_curr_pwd(void);				/* check current directory and rewrite PWD and g_curr_dir variables if it is invalid */

#endif
