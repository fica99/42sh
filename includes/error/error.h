/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:56:22 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 20:46:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ENOENT 2
# define ENOMEM 12
# define EACCES 13

void			ft_perror(char *str);
void			pr_gen_perror(void);
void			print_error(char *name, char *str, char *command, int p);
void			print_error_withoutexit(char *name, char *str, char *command,
				int p);
#endif
