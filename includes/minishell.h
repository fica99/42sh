/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/16 20:34:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <unistd.h>

uint8_t	echo(int argc, char **argv, char **env);
void	echo_find_flags(char **argv, unsigned short *i, uint8_t *j);

uint8_t	cd(int argc, char **argv, char **env);

uint8_t	get_argc_env(char *arr, char **env);
#endif
