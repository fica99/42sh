/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:56:22 by filip             #+#    #+#             */
/*   Updated: 2019/09/21 22:22:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define NOERROR NULL
# define ENOENT "No such file or directory"
# define EBADF "Bad file descriptor"
# define ENOMEM "Cannot allocate memory"
# define EACCES "Permission denied"
# define EFAULT "Bad address (POSIX.1-2001)"
# define EHRDCPY "the terminal is hardcopy, cannot be used for application"
# define ENTFND "the terminal not found, having no information for application"
# define ENOTERMINFO "the terminfo database could not be found"

/*
**	ft_errno.c
*/
void			err_exit(char *str, char *command, char *err);
void			err(char *str, char *command, char *err);
void			ft_error(char *str, char *command, char *err);
#endif
