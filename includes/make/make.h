/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:07:13 by filip             #+#    #+#             */
/*   Updated: 2019/09/21 20:00:50 by aashara-         ###   ########.fr       */
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

/*
**	buff_editing.c
*/
char			*copy_from_buff(char *buffer, char *new_buffer, short start,
short end);
char			check_print_arr(char *arr);
/*
**	env.c
*/
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			print_environ(void);
/*
**	env2.c
*/
char			*get_folder(void);
char			*get_path(void);
/*
**	process.c
*/
pid_t			make_process(void);
#endif
