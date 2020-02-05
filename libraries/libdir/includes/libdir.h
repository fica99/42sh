/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libdir.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 23:42:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 23:42:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDIR_H
# define LIBDIR_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>

size_t	ft_size_dir(char *dirpath);
short	ft_dir_flag(short flag, unsigned char d_type);
char	**ft_dir_content(char *dirpath, short flag);
char	ft_file_type(char *path);
void	ft_write_to_file(char *path, int flags, int perm, char *content);
char	*ft_read_file(char *path);
#endif
