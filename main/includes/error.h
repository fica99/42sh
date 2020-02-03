/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:10:35 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/03 22:57:41 by aashara-         ###   ########.fr       */
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

/*
**			error.c
*/
void		err_exit(char *name, char *str, char *command, char *err);
void		err(char *name, char *str, char *command, char *err);
#endif
