/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 21:36:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 256
uint8_t	echo(int argc, char **argv, char **env);
uint8_t	echo_find_flags(char **argv, unsigned short *i);

uint8_t	cd(int argc, char **argv, char **env);

uint8_t	check_ch_dir(int argc , char **argv, char **env);
uint8_t	check_request(int argc, char  **argv, char **env);

short	get_count_var(char *arr, char **env);
char	*get_var(char *arr, char **env);

uint8_t	add_flag(uint8_t flags, char flag);
uint8_t	is_flags(uint8_t flags, char flag);
void	ft_putstr_ecr(char *arr);
uint8_t	check_symbol(char s);
#endif
