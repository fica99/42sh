/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:07:13 by filip             #+#    #+#             */
/*   Updated: 2019/08/03 00:26:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_H
# define MAKE_H

# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>

char			*ft_getenv(char *arr);
short			get_count_var(char *arr);
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			print_environ(void);
char			*get_folder(void);
char			*get_path(void);
pid_t			make_process(void);
char			check_print_arr(char *arr);
char			*copy_from_buff(char *buffer, char *new_buffer, short start,
short end);
#endif
