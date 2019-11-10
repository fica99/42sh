/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:15:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 17:18:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define MAXDIR 4097
# define CD_USAGE "cd: usage: cd [-L|-P] [dir]"
# define PWD_USAGE "usage: pwd [-LP]"

char *g_curr_dir; 					/* containing current logical path or physical if -P is active */

typedef struct s_cdf
{
	char		P;
	char 		L;
}				t_cdf;

int				change_wdir(char *path, t_cdf flags);
void			pwd(char **av);
void			cd(char **av);
void			rewrite(char *path, t_cdf flags);			/* rewrite current logical pwd */
char			check_request(char **argv, char *path);
void			ft_echo(int argc, char **argv, char **env_cp);
void			env(int argc, char **argv, char **env_cp);
void			print_bin_table(t_hash **bin_table, size_t size);
void			print_history(t_history *history_buff);
void			set_env(int argc, char **argv, char **env_cp);
void			unset_env(int argc, char **argv, char **env_cp);
void			init_curr_pwd(void);				/* check current directory and rewrite PWD and g_curr_dir variables if it is invalid */

#endif
