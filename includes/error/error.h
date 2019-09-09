/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:56:22 by filip             #+#    #+#             */
/*   Updated: 2019/09/09 22:37:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define NOERROR 0
# define ENOENT 2
# define EBADF 9
# define ENOMEM 12
# define EACCES 13
# define EFAULT 14
# define EHRDCPY "the terminal is hardcopy, cannot be used for application"
# define ENTFND "the terminal not found, having no information for application"
# define ENOTERMINFO "the terminfo database could not be found"

/*
**	ft_errno.c
*/
void			print_error(char *name, char *str, char *command, int p);
void			ft_perror(char *str);
void			pr_gen_perror(void);
void			print_error_withoutexit(char *name, char *str, char *command,
				int p);
#endif
