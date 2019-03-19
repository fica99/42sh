/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 18:49:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>

# define MAXDIR 256
uint8_t	echo(int argc, char **argv, char **env);
void	echo_find_flags(char **argv, unsigned short *i, uint8_t *j);

uint8_t	cd(int argc, char **argv, char **env);

short	get_count_var(char *arr, char **env);
char	*get_var(char *arr, char **env);
#endif
