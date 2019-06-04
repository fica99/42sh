/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:56:22 by filip             #+#    #+#             */
/*   Updated: 2019/06/04 19:46:37 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ENOENT 2
# define ENOMEM 12
# define EACCES 13

void			print_error(char *name, char *str, char *command, int p);
void			ft_perror(char *str);
void			pr_gen_perror(void);
void			print_error_withoutexit(char *name, char *str, char *command,
				int p);
#endif
