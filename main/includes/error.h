/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:10:35 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/19 17:01:12 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# define ENOMEM "Cannot allocate memory"
# define NOERROR NULL
# define EHRDCPY "the terminal is hardcopy, cannot be used for application"
# define ENTFND "the terminal not found, having no information for application"
# define ENOTERMINFO "the terminfo database could not be found"
# define EACCES "Permission denied"
# define ENOTFND "not found"
# define EUEOF "unexpected end of file"
# define EUEOFMSQ "unexpected EOF while looking for matching '\''"
# define EUEOFMDQ "unexpected EOF while looking for matching '\"'"
# define EUEOFMSB "unexpected EOF while looking for matching ')'"
# define EUEOFMFB "unexpected EOF while looking for matching '}'"
# define EBADFD "Bad file descriptor"

/*
**			error.c
*/
int			fix_exit(int status);
void		err_exit(char *name, char *str, char *command, char *err);
void		err(char *name, char *str, char *command, char *err);
#endif
