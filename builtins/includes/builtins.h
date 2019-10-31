/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:15:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/31 22:51:05 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define MAXDIR 4097

void			cd(int argc, char **argv, char **env_cp);
void			check_ch_dir(int argc, char **argv);
char			check_request(char **argv, char *path);
char			*check_cdpath(char *path);
void			ft_echo(int argc, char **argv, char **env_cp);
void			env(int argc, char **argv, char **env_cp);
void			print_bin_table(t_hash **bin_table, size_t size);
void			set_env(int argc, char **argv, char **env_cp);
void			unset_env(int argc, char **argv, char **env_cp);
#endif
